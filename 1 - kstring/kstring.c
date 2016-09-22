#include "kstring.h"
#include <stdlib.h>

char kstrget(kstring str, size_t pos)
{
	if (pos >= str.length) {
		abort(); //NO
	}	
	else {
		return str.data[pos];
	}
}

void kstrput(kstring str, size_t pos, char ch)
{
	if (pos >= str.length) {
                abort(); //NO
        }
        else {
                str.data[pos] = ch;
		return;
        }	
}

size_t kstrlen(kstring str)
{
	return str.length;
}

kstring kstralloc(size_t nbytes)
{
	kstring result = { NULL, 0 };
	if ((result.data = malloc(nbytes))) {
		//make all the data \0
		for (int i=0;i<nbytes;i++) {
			result.data[i] = '\0';
		}
		result.length = nbytes;
		return result;
	}
	//otherwise, a null pointer returned. AKA memory allocation FAILURE
	else {
		abort();
	}
}

kstring kstrfrom(const char *cstr)
{
	//first, find the length of the c-string
	int len = 0;
	while (cstr[len] != '\0') {
		len++;
	}
	len++; //null terminator counts in length
		
	//now allocate memory for the new kstring
	kstring result = kstralloc(len);
	
	//since we have the right length, save it in the kstring
	result.length = len;
	
	//copy the data over
	for (int i=0;i<(len-1);i++) {
		result.data[i] = cstr[i];
	}

	//and now put in a null delimiter thing
	//result.data[len] = '\0';
	//JK that's actually taken care of in the kstralloc function!	

	return result;
}

void kstrfree(kstring str)
{
	free(str.data);

}

void kstrextend(kstring *strp, size_t nbytes)
{
	//if the length need not be extended, return without changing anything
	if (strp->length >= nbytes) {
		return;
	} 
	else {
		if ((strp->data = realloc(strp->data, nbytes))) {
			//step3: fill in with null character delimiters
			for (int i=strp->length;i<nbytes;i++) {
				strp->data[i] = '\0';
			}
			strp->length = nbytes;
		}
		else {
			abort();
		}
	}
	return;
}

void kstrcat(kstring *destp, kstring src)
{
	//gotta save oldlen, as that length is lost after calling kstrextend
	int oldlen = destp->length;
	kstrextend(destp, (destp->length + src.length));
	for (int i=oldlen;i<destp->length;i++) {
		//copy data over from the source string to the destination string (offset by oldlen)
		destp->data[i] = src.data[i-oldlen];
	}
	return;
}
