#include <vector>
#include <string>
#include "gapbuffer.h"

void GapBuffer::insert(char data){
	*gap_start {data};
	gap_start += 1;
}

void GapBuffer::moveleft(){
	if(gap_start == &buffer[0]){
		return;
	}
	
	//check left side
	char* target {gap_start-1};
	
	//move to rightmost side of the gap (right before gap end)
	char* rightmost = gap_end-1;
	*rightmost = *target;
	//move gap start and gap_right to the left
	gap_start -= 1;
	gap_end -= 1;
}

void GapBuffer::moveright(){
	char* buffer_end {buffer.data() + buffer.size()};

	if(gap_end == buffer_end){
		return;
	}
	
	char* target {gap_end};
	
	char* leftmost = gap_start;
	*leftmost = *target;

	gap_start += 1;
	gap_end += 1;
}




