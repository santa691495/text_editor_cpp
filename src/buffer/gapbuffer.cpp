#include <vector>
#include <string>
#include <algorithm>
#include "gapbuffer.h"

void GapBuffer::insert(char data){
	*gap_start = data;
	gap_start += 1;
}

void GapBuffer::move_left(){
	if(gap_start == &buffer[0]){
		return;
	}
	
	//check left side
	char* target {gap_start-1};
	
	//move to rightmost side of the gap (right before gap end)
	char* rightmost {gap_end-1};
	*rightmost = *target;
	//move gap start and gap_right to the left
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

