#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	char *fifo1 = "fifo1";
	char *fifo2 = "fifo2";
	char ch, buffer[100];
	int d1, i = 0;
	
		mkfifo(fifo1, 0666);
		d1 = open(fifo1, O_WRONLY);
			printf("\nEnter data (end with #): ");
		ch = getchar();
		while (ch != '#') {
			buffer[i] = ch;
			i++;
			ch = getchar();
		}
	
		buffer[i] = '#';
		write(d1, buffer, sizeof(buffer));
		close(d1);

	sleep(2);

	int d2 = open(fifo2, O_RDONLY);
	char buffer2[100];
		read(d2, buffer2, sizeof(buffer2));
			printf("User2: %s\n", buffer2);
		close(d2);

	FILE *fptr = fopen(buffer2, "r");
		if (fptr == NULL) {
			perror("Error opening file");
			return 1;
		}

		while ((ch = fgetc(fptr)) != EOF) {
			printf("%c", ch);
		}
	fclose(fptr);
return 0;
}