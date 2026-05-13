#include <vector>
#include <string>
#include "gapbuffer.h"

void GapBuffer::insert(char data){
	*gap_start = data;
	gap_start += 1;
}

void GapBuffer::move_left(){
	if(gap_start == &buffer[0]){
		return;
	}

	char* target {gap_start-1};

	char* rightmost {gap_end-1};
	*rightmost = *target;

	gap_start -= 1;
	gap_end -= 1;
}

void GapBuffer::move_right(){
	char* buffer_end {buffer.data() + buffer.size()};

	if(gap_end == buffer_end){
		return;
	}

	char* target {gap_end};

	char* leftmost {gap_start};
	*leftmost = *target;

	gap_start += 1;
	gap_end += 1;
}

void GapBuffer::grow(){
	size_t new_gap_size {buffer.size()};

	char* old_base = buffer.data();
	char* old_end = old_base + buffer.size();

	std::vector<char> new_buffer(buffer.size()*2);
	char* new_base = new_buffer.data();

	size_t left_size = gap_start - old_base;
	size_t right_size = old_end - gap_end;

	char* new_gap_start = new_base + left_size;
	char* new_gap_end  = new_base + new_buffer.size() - right_size;

	for(char* src = old_base, *dst = new_base; src < gap_start; ++src, ++dst){
		*dst = *src;
	}

	for(char* src = gap_end, *dst = new_gap_end; src < old_end; ++src, ++dst){
		*dst = *src;
	}

	buffer = std::move(new_buffer);

	gap_start = new_gap_start;
	gap_end = new_gap_end;
}

bool GapBuffer::is_growable(){
	std::string current_text { get_text() };

	if(current_text.size() < get_current_size()){
		return false;
	}

	return true;
}

std::string GapBuffer::get_text(){
	std::string text;

	size_t current_gap_size = gap_end - gap_start;
	size_t reserve_amnt = buffer.size() - current_gap_size;
	text.reserve(reserve_amnt);

	char* buffer_start = buffer.data();
	char* buffer_end = buffer.data() + buffer.size();

	size_t left_size = gap_start - buffer_start;
	size_t right_size = buffer_end - gap_end;

	text.append(buffer_start, left_size);
	text.append(gap_end, right_size);

	return text;
}

size_t GapBuffer::get_current_size(){
	size_t current_size {buffer.size()};
	return current_size;
}

void GapBuffer::backspace(){
	if(gap_start == &buffer[0]){
		return;
	}

	gap_start -= 1;
}

void GapBuffer::clear(){
	gap_start = buffer.data();
	gap_end = buffer.data()+buffer.size();
}

bool GapBuffer::move_right_line(){

	if(gap_end == buffer.data() +  buffer.size()){
		return false;
	}

	char* finder = gap_end;
	while(*finder != '\n' && finder != buffer.data() + buffer.size()){
	    ++finder;
	}

	if(finder == buffer.data() + buffer.size()){
	    return false;
	}

	while(gap_end != finder+1){
		move_right();
	}

	return true;
}

bool GapBuffer::move_left_line() {
    if (gap_start == buffer.data()) {
        return false;
    }

    char* finder = gap_start - 1;
    while (finder >= buffer.data() && *finder != '\n') {
        --finder;
    }

    if (finder < buffer.data() || *finder != '\n') {
        return false;
    }

    char* line_end = finder;
    --finder;

    while (finder >= buffer.data() && *finder != '\n') {
        --finder;
    }

    char* target;
    if (finder < buffer.data() || *finder != '\n') {
        target = buffer.data();
    } else {
        target = finder + 1;
    }

    while (gap_start != target) {
        move_left();
    }

    return true;
}

bool GapBuffer::move_startln_up(){
	return move_left_line();
}

bool GapBuffer::move_startln_down(){
	return move_right_line();
}

bool GapBuffer::is_at_line_start() {
	if(gap_start == buffer.data()){
		return true;
	}
	if(*(gap_start-1) == '\n'){
		return true;
	}
	return false;
}

bool GapBuffer::is_at_line_edge() {
	if(gap_end == buffer.data() + buffer.size()){
		return true;
	}
	if(*gap_end == '\n'){
		return true;
	}
	return false;
}

void GapBuffer::move_to_start(){
	while(gap_start != buffer.data()){
		move_left();
	}
}
