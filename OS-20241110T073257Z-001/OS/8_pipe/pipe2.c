#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	char *fifo1 = "fifo1";
	char *fifo2 = "fifo2";
	char buffer1[100];
	int d1, d2, i = 0, cc = 0, ln = 0, wc = 0;
	
		d1 = open(fifo1, O_RDONLY);
		read(d1, buffer1, sizeof(buffer1));

		while (buffer1[i] != '#' && buffer1[i] != '\0') {
			if (buffer1[i] == ' ') {
				wc++;
			} 
			else if (buffer1[i] == '\n') {
				ln++;
				wc++;
			} else {
				cc++;
			}

			i++;
		}

	FILE *fp = fopen("memory.txt", "w");
		if (fp == NULL) {
			perror("Error opening file");
			return 1;
		}
		fprintf(fp, "\nLine count = %d", ln);
		fprintf(fp, "\nWord count = %d", wc);
		fprintf(fp, "\nCharacter count = %d", cc);
	fclose(fp);

	mkfifo(fifo2, 0666);
	d2 = open(fifo2, O_WRONLY);
	write(d2, "memory.txt", 11);
	close(d2);
	
return 0;
}