#include "../inc/libmx.h"

void mx_print_unicode(wchar_t c) {
    char str[4];
    int len;

	if (c < 0x80) {
		str[0] = (c >> 0 & 0x7F) | 0x00;
        len = 1;
	}
    else if (c < 0x0800) {
		str[0] = (c >> 6 & 0x1F) | 0xC0;
		str[1] = (c >> 0 & 0x3F) | 0x80;
        len = 2;
	}
    else if (c < 0x010000) {
		str[0] = (c >> 12 & 0x0F) | 0xE0;
		str[1] = (c >> 6 & 0x3F) | 0x80;
		str[2] = (c >> 0 & 0x3F) | 0x80;
        len = 3;
    }
    else {
		str[0] = (c >> 18 & 0x07) | 0xF0;
		str[1] = (c >> 12 & 0x3F) | 0x80;
		str[2] = (c >> 6 & 0x3F) | 0x80;
		str[3] = (c >> 0 & 0x3F) | 0x80;
        len = 4;
	}
    write(1, str, len);
}

// int main() {
//     //wchar_t c = 0x72d7;
//     // char nl = '\n';

//     for (wchar_t a = 0x0; a < 0x3e8; a++) {
//         printf("%#08x)   ", a);
//         mx_print_unicode(a);
//         printf("\n");
//     }
// }
