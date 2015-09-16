#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FreeImage.h>

#define APPNAME "png2pofo"
#define APPDESC "Converts PNG image to formats displayable on Atari Portfolio - PGF or PGC.\nSource image dimensions must be 240x64 pixels with 1-bit colour depth."
#define APPVER "1.024"
#define AUTHOR "Martin \"Logout\" Kukac"
#define MAIL "logout128@gmail.com"
#define WEB "http://i-logout.cz"
#define VRAM_SIZE 1920

int main(int argc, char **argv) {
	FIBITMAP *bitmap;
	char *target, *buffer;
	FILE *f_out;
	int  i;
	unsigned char y;
	int pack = 0;
	int argstart = 1;
	const char pack_header[3] = {0x50,0x47,0x01};
	
	if (argc<2) {
		fprintf(stderr, "%s: No parameters given. Use \"%s -h\" for help.\n", APPNAME, APPNAME);
		return 128;
	}
	else {
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			printf(
				APPNAME"\n"
				APPDESC"\n"
				"Usage: "APPNAME" [options] input output\n"
				"Options:\n"
				"\t-c, --compress\t\toutput will be in PGC compressed format\n"
				"\t-h, --help\t\tthis help message\n"
				"\t-v, --version\t\tversion and contact to the author\n"
			);
			return 0;
		}
		else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
			printf(
				APPNAME " " APPVER "\n"
				"Author: "AUTHOR " (" MAIL ")\n"
				"Website: " WEB "\n"
			);
			return 0;
		}
		else if (!strcmp(argv[1], "-c") || !strcmp(argv[1], "--compress")) {
			pack=1;
			argstart=2;
		}
		else if (argv[1][1] == '-') {
			fprintf(stderr, "%s: Parameter \"%c\" not known. Use \"%s -h\" for help.\n", APPNAME, argv[1][1], APPNAME);
		}
	
		printf("%s\n", APPNAME);	
		printf("Input file: %s\n", argv[argstart]);						
		FreeImage_Initialise(0);	

		if ((bitmap = FreeImage_Load(FIF_PNG, argv[argstart], PNG_DEFAULT))) {			
			if (FreeImage_GetBPP(bitmap)!=1) {
				fprintf(stderr, "Error: Colour depth %d-bit, supposed to be 1-bit.\n", FreeImage_GetBPP(bitmap));
				return 32;
			}
			else if (FreeImage_GetWidth(bitmap)!=240 && FreeImage_GetHeight(bitmap)!=64) {
				fprintf(stderr, "Error: Dimensions %dx%d pixels, supposed to be 240x64 pixels.\n", FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap));
				return 32;
			}
			else {
				f_out = fopen(argv[argstart+1], "wb");
				if (!f_out) {
					fprintf(stderr, "Error: Cannot create output file.\n");
					return 64;
				}						
				printf("Output file: %s\n", argv[argstart+1]);	
				target = (char *) malloc(VRAM_SIZE*sizeof(char));
				for (i=0; i<64; i++) {
					for(y=0; y<30; y++) {
						target[i*30+y] = FreeImage_GetScanLine(bitmap, 63-i)[y];
					}
				}

				if (pack) {
					fwrite(pack_header,1,3, f_out);
					i=0;
					buffer = (char*) malloc(VRAM_SIZE*sizeof(char));
					while (i<VRAM_SIZE) {
						y=0;
						if (target[i]==target[i+1]) {
							do {
								y++;
								i++;
							} while(target[i-1]==target[i] && (y<127) && (i<VRAM_SIZE));
							
							y = y|128;
							fwrite(&y, 1,1, f_out);
							fwrite(&(target[i-1]), 1,1, f_out);
						}	
						else {
							do {
								buffer[y] = target[i];
								y++;
								i++;
							} while(target[i]!=target[i+1] && (y<127) && (i<VRAM_SIZE));
							fwrite(&y,1,1, f_out);
							fwrite(buffer, 1, y, f_out);
						}																				
					}
				}
				else {
					fwrite(target, 1, VRAM_SIZE, f_out);
				}
				free(buffer);
				free(target);
				fclose(f_out);											
			}
		}
		else {
			fprintf(stderr, "Error: Cannot open input file. It is either corrupted or not a PNG image.\n");
			return 64;
		}	
		return 0;
	}
}
