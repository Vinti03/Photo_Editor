#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct imagine {
int height, width;
union pixel {
	struct culoare {
		int R, G, B;
	} color;
	struct gri {
		int intensity;
	} tone;
} **M;
} img, aux;

void free_image(struct imagine *img, int n)
{
	for (int i = 0; i < n; i++)
		free(img->M[i]);
	free(img->M);

	img->height = 0;
	img->width = 0;
}

void copy_struct(struct imagine *img, struct imagine *aux, int h, int w)
{
	(*aux).height = h;
	(*aux).width = w;
	//aloca matrice
	(*aux).M = (union pixel **)calloc(h, sizeof(union pixel *));
	if (!(*aux).M) {
		printf("Could not access the memory\n");
		exit(-11);
	}
	for (int i = 0; i < h; i++) {
		(*aux).M[i] = (union pixel *)calloc(w, sizeof(union pixel));
		if (!(*aux).M[i]) {
			printf("Could not access the memory\n");
			exit(-11);
		}
	}
	//
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			(*aux).M[i][j].tone.intensity = (*img).M[i][j].tone.intensity;
			(*aux).M[i][j].color.R = (*img).M[i][j].color.R;
			(*aux).M[i][j].color.G = (*img).M[i][j].color.G;
			(*aux).M[i][j].color.B = (*img).M[i][j].color.B;
		}
}

void citeste_antet(char c, FILE *f, int *n, int  *m, int *h)
{
	*n = *m = *h = 0;
	c = fgetc(f);//whitespace at the end of row 1
	c = fgetc(f);//begging of the first number
	while (c >= '0' && c <= '9') {
		(*m) = (*m) * 10 + (c - '0');
		c = fgetc(f);
	}
	c = fgetc(f);//begging of the second number
	while (c >= '0' && c <= '9') {
		(*n) = (*n) * 10 + (c - '0');
		c = fgetc(f);
	}
	c = fgetc(f);//begging of the 3rd row
	while (c >= '0' && c <= '9') {
		(*h) = (*h) * 10 + (c - '0');
		c = fgetc(f);
	}
}

void load_P2(int n, int m, char *nume_fisier, FILE *f, struct imagine *img)
{
	//alocare
	(*img).height = n;
	(*img).width = m;
	(*img).M = (union pixel **)calloc(n, sizeof(union pixel *));
	if (!(*img).M) {
		printf("Failed to load %s\n", nume_fisier);
		exit(-11);
	}
	for (int i = 0; i < n; i++) {
		(*img).M[i] = (union pixel *)calloc(m, sizeof(union pixel));
		if (!(*img).M[i]) {
			printf("Failed to load %s\n", nume_fisier);
			exit(-11);
		}
	}

	//atribuire
	char c;
	int k = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			c = fgetc(f);
			while (c < '0' || c > '9')
				c = fgetc(f);
			while (c >= '0' && c <= '9') {
				(*img).M[i][j].tone.intensity = (*img).M[i][j].tone.intensity *
				10 + (c - '0');
				c = fgetc(f);
			}
			k++;
		}
	//mesaj
	printf("Loaded %s\n", nume_fisier);
}

void load_P3(int n, int m, char *nume_fisier, FILE *f, struct imagine *img)
{
	//alocare
	(*img).height = n;
	(*img).width = m;
	(*img).M = (union pixel **)calloc(n, sizeof(union pixel *));
	if (!(*img).M) {
		printf("Failed to load %s\n", nume_fisier);
		exit(-11);
	}
	for (int i = 0; i < n; i++) {
		(*img).M[i] = (union pixel *)calloc(m, sizeof(union pixel));
		if (!(*img).M[i]) {
			printf("Failed to load %s\n", nume_fisier);
			exit(-11);
		}
	}

	//atribuire
	char c;
	int k = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			//R
			c = fgetc(f);
			while (c < '0' || c > '9')
				c = fgetc(f);
			while (c >= '0' && c <= '9') {
				(*img).M[i][j].color.R = (*img).M[i][j].color.R * 10 +
				(c - '0');
				c = fgetc(f);
			}
			//G
			c = fgetc(f);
			while (c < '0' || c > '9')
				c = fgetc(f);
			while (c >= '0' && c <= '9') {
				(*img).M[i][j].color.G = (*img).M[i][j].color.G * 10 +
				(c - '0');
				c = fgetc(f);
			}
			//B
			c = fgetc(f);
			while (c < '0' || c > '9')
				c = fgetc(f);
			while (c >= '0' && c <= '9') {
				(*img).M[i][j].color.B = (*img).M[i][j].color.B * 10 +
				(c - '0');
				c = fgetc(f);
			}
			k++;
		}
	//mesaj
	printf("Loaded %s\n", nume_fisier);
}

void load_P5(int n, int m, char *nume_fisier, FILE *f, struct imagine *img,
			 int distanta)
{
	//alocare
	(*img).height = n;
	(*img).width = m;
	(*img).M = (union pixel **)calloc(n, sizeof(union pixel *));
	if (!(*img).M) {
		printf("Failed to load %s\n", nume_fisier);
		exit(-11);
	}
	for (int i = 0; i < n; i++) {
		(*img).M[i] = (union pixel *)calloc(m, sizeof(union pixel));
		if (!(*img).M[i]) {
			printf("Failed to load %s\n", nume_fisier);
			exit(-11);
		}
	}

	// //atribuire
	fseek(f, distanta, SEEK_SET);
	unsigned char *aux;
	aux = (unsigned char *)calloc(n * m, sizeof(unsigned char));
	if (!aux) {
		printf("Could not acces memory\n");
		exit(-11);
	}

	fread(aux, sizeof(unsigned char), n * m, f);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			(*img).M[i][j].tone.intensity = (int)(aux[m * i + j]);
	//free aux
	free(aux);
	// //mesaj
	printf("Loaded %s\n", nume_fisier);
}

void load_P6(int n, int m, char *nume_fisier, FILE *f, struct imagine *img,
			 int distanta)
{
	//alocare
	(*img).height = n;
	(*img).width = m;
	(*img).M = (union pixel **)calloc(n, sizeof(union pixel *));
	if (!(*img).M) {
		printf("Failed to load %s\n", nume_fisier);
		exit(-11);
	}
	for (int i = 0; i < n; i++) {
		(*img).M[i] = (union pixel *)calloc(m, sizeof(union pixel));
		if (!(*img).M[i]) {
			printf("Failed to load %s\n", nume_fisier);
			exit(-11);
		}
	}

	//atribuire
	fseek(f, distanta, SEEK_SET);
	unsigned char *aux;
	aux = (unsigned char *)calloc(3 * n * m, sizeof(unsigned char));
	if (!aux) {
		printf("Could not acces memory\n");
		exit(-11);
	}

	fread(aux, sizeof(unsigned char), 3 * n * m, f);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3 * m; j++) {
			if (j % 3 == 0)
				(*img).M[i][j / 3].color.R = aux[3 * m * i + j];
			else if (j % 3 == 1)
				(*img).M[i][j / 3].color.G = aux[3 * m * i + j];
			else
				(*img).M[i][j / 3].color.B = aux[3 * m * i + j];
		}
	//free aux
	free(aux);
	//mesaj
	printf("Loaded %s\n", nume_fisier);
}

void select_all(int n, int m, int *x1, int *x2, int *y1, int *y2)
{
	if (n == 0 || m == 0) {
		printf("No image loaded\n");
	} else {
		*x1 = *y1 = 0;
		*x2 = m;
		*y2 = n;
		printf("Selected ALL\n");
	}
}

void SELECT(int *x1, int *x2, int *y1, int *y2, int n, int m, char comanda[])
{
	int k, xx1, xx2, yy1, yy2, a, b, c, d, nr;
	xx1 = *x1;
	xx2 = *x2;
	yy1 = *y1;
	yy2 = *y2;
	k = 7;
	*x1 = *x2 = *y1 = *y2 = 0;
	a = 0;
	b = 0;
	c = 0;
	d = 0;
	nr = 0;
	//x1
	while ((comanda[k] >= '0' && comanda[k] <= '9') || comanda[k] == '-' ||
		   comanda[k] == '+') {
		*x1 = *x1 * 10 + (comanda[k] - '0');
		a = 1;
		k++;
	}
	k++;
	//y1
	while ((comanda[k] >= '0' && comanda[k] <= '9') || comanda[k] == '-' ||
		   comanda[k] == '+') {
		*y1 = *y1 * 10 + (comanda[k] - '0');
		b = 1;
		k++;
	}
	k++;
	//x2
	while ((comanda[k] >= '0' && comanda[k] <= '9') || comanda[k] == '-' ||
		   comanda[k] == '+') {
		*x2 = *x2 * 10 + (comanda[k] - '0');
		c = 1;
		k++;
	}
	k++;
	//y2
	while ((comanda[k] >= '0' && comanda[k] <= '9') || comanda[k] == '-' ||
		   comanda[k] == '+') {
		*y2 = *y2 * 10 + (comanda[k] - '0');
		d = 1;
		k++;
	}
	nr = a + b + c + d;
	if (nr != 4) {
		printf("Invalid command\n");
		*x1 = xx1;
		*x2 = xx2;
		*y1 = yy1;
		*y2 = yy2;
	} else {
		if (*x2 < *x1) {
			int aux = *x2;
			*x2 = *x1;
			*x1 = aux;
		}
		if (*y2 < *y1) {
			int aux = *y2;
			*y2 = *y1;
			*y1 = aux;
		}
		if (n == 0 || m == 0) {
			printf("No image loaded\n");
		} else if ((*x1 < 0 || *x1 > m || *x2 < 0 || *x2 > m || *y1 < 0 ||
				   *y1 > n || *y2 < 0 || *y2 > n) || (*x1 == *x2 ||
				   *y1 == *y2) || (*x1 > *x2 || *y1 > *y2)) {
			printf("Invalid set of coordinates\n");
			*x1 = xx1;
			*x2 = xx2;
			*y1 = yy1;
			*y2 = yy2;
		} else {
			printf("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
		}
	}
}

void CROP(int *height, int *width, int *x1, int *x2, int *y1, int *y2,
		  struct imagine *img)
{
	if (img->height == 0 || img->width == 0) {
		printf("No image loaded\n");
	} else {
		struct imagine aux;
		copy_struct(&(*img), &aux, *height, *width);
		//free img
		for (int i = 0; i < *height; i++)
			free((*img).M[i]);
		free((*img).M);
		//
		(*img).M = (union pixel **)malloc((*y2 - *y1) * sizeof(union pixel *));
		if (!(*img).M) {
			printf("Could not access the memory\n");
			exit(-11);
		}
		for (int i = 0; i < *y2 - *y1; i++) {
			(*img).M[i] = (union pixel *)malloc((*x2 - *x1) *
			sizeof(union pixel));
			if (!(*img).M[i]) {
				printf("Could not access the memory\n");
				exit(-11);
			}
		}

		for (int i = 0; i < *y2 - *y1; i++)
			for (int j = 0; j < *x2 - *x1; j++)
				(*img).M[i][j] = aux.M[*y1 + i][*x1 + j];
		// //free aux
		free_image(&aux, *height);

		*height = *y2 - *y1;
		*width =  *x2 - *x1;
		*x1 = *y1 = 0;
		*x2 = *width;
		*y2 = *height;
		printf("Image cropped\n");
	}
}

void free_aux(union pixel ***aux, int n)
{
	for (int i = 0; i < n; i++)
		free((*aux)[i]);
	free(*aux);
}

void SAVE(char *comanda, char P, struct imagine img, int h)
{
	if (img.height == 0 || img.width == 0) {
		printf("No image loaded\n");
	} else {
		char fisier[256];
		int save_ascii = 0, i = 0;
		strcpy(fisier, comanda + 5);
		while (i < (int)(strlen(fisier)) && fisier[i] != ' ')
			i++;
		if (i + 2 < (int)(strlen(fisier)))
			save_ascii = 1;
		fisier[i] = 0;
		if (save_ascii) {
			FILE *g = fopen(fisier, "w");
			if (P == '2' || P == '3')
				fprintf(g, "P%c\n", P);
			else
				fprintf(g, "P%c\n", (char)(P - 3));
			fprintf(g, "%d %d\n", img.width, img.height);
			fprintf(g, "%d\n", h);
			//
			if (P == '2' || P == '5') {
				for (int i = 0; i < img.height; i++) {
					for (int j = 0; j < img.width; j++)
						fprintf(g, "%d ", img.M[i][j].tone.intensity);
					fprintf(g, "\n");
				}
			} else {
				for (int i = 0; i < img.height; i++) {
					for (int j = 0; j < img.width; j++)
						fprintf(g, "%d %d %d ", img.M[i][j].color.R,
								img.M[i][j].color.G, img.M[i][j].color.B);
					fprintf(g, "\n");
				}
			}
			fclose(g);
		} else {
			FILE *g = fopen(fisier, "wb");
			if (P == '2' || P == '3')
				fprintf(g, "P%c\n", (char)(P + 3));
			else
				fprintf(g, "P%c\n", P);
			fprintf(g, "%d %d\n", img.width, img.height);
			fprintf(g, "%d\n", h);
			//
			unsigned char *aux;
			if (P == '2' || P == '5') {
				aux = (unsigned char *)calloc(img.height * img.width,
				sizeof(unsigned char));
				if (!aux) {
					printf("Could not access memory!");
					exit(-11);
				}
				for (int i = 0; i < img.height; i++)
					for (int j = 0; j < img.width; j++)
						aux[img.width * i + j] = (unsigned char)
						(img.M[i][j].tone.intensity);
				fwrite(aux, sizeof(unsigned char), img.height * img.width, g);
			} else {
				aux = (unsigned char *)malloc(3 * img.height * img.width *
				sizeof(unsigned char));
				if (!aux)
					printf("Could not access memory!"), exit(-11);
				for (int i = 0; i < img.height; i++)
					for (int j = 0; j < img.width; j++) {
						aux[3 * (img.width * i + j)] = (unsigned char)
						(img.M[i][j].color.R);
						aux[3 * (img.width * i + j) + 1] = (unsigned char)
						(img.M[i][j].color.G);
						aux[3 * (img.width * i + j) + 2] = (unsigned char)
						(img.M[i][j].color.B);
					}
				fwrite(aux, sizeof(unsigned char), 3 * img.height * img.width,
					   g);
			}
			free(aux);
			fclose(g);
		}
		printf("Saved %s\n", fisier);
	}
}

int clamp(int x)
{
	if (x < 0)
		x = 0;
	else if (x > 255)
		x = 255;
	return x;
}

void edge(struct imagine *img, struct imagine aux, int i, int j)
{
	(*img).M[i][j].color.R = clamp(aux.M[i - 1][j - 1].color.R * (-1) +
								aux.M[i - 1][j].color.R * (-1) +
								aux.M[i - 1][j + 1].color.R * (-1) +
								aux.M[i][j - 1].color.R * (-1) +
								aux.M[i][j].color.R * (8) +
								aux.M[i][j + 1].color.R * (-1) +
								aux.M[i + 1][j - 1].color.R * (-1) +
								aux.M[i + 1][j].color.R * (-1) +
								aux.M[i + 1][j + 1].color.R * (-1));
				(*img).M[i][j].color.G = clamp(aux.M[i - 1][j - 1].color.G *
											   (-1) +
								aux.M[i - 1][j].color.G * (-1) +
								aux.M[i - 1][j + 1].color.G * (-1) +
								aux.M[i][j - 1].color.G * (-1) +
								aux.M[i][j].color.G * (8) +
								aux.M[i][j + 1].color.G * (-1) +
								aux.M[i + 1][j - 1].color.G * (-1) +
								aux.M[i + 1][j].color.G * (-1) +
								aux.M[i + 1][j + 1].color.G * (-1));
				(*img).M[i][j].color.B = clamp(aux.M[i - 1][j - 1].color.B *
											   (-1) +
								aux.M[i - 1][j].color.B * (-1) +
								aux.M[i - 1][j + 1].color.B * (-1) +
								aux.M[i][j - 1].color.B * (-1) +
								aux.M[i][j].color.B * (8) +
								aux.M[i][j + 1].color.B * (-1) +
								aux.M[i + 1][j - 1].color.B * (-1) +
								aux.M[i + 1][j].color.B * (-1) +
								aux.M[i + 1][j + 1].color.B * (-1));
}

void sharpen(struct imagine *img, struct imagine aux, int i, int j)
{
	(*img).M[i][j].color.R = clamp(aux.M[i - 1][j - 1].color.R * (0) +
								aux.M[i - 1][j].color.R * (-1) +
								aux.M[i - 1][j + 1].color.R * (0) +
								aux.M[i][j - 1].color.R * (-1) +
								aux.M[i][j].color.R * (5) +
								aux.M[i][j + 1].color.R * (-1) +
								aux.M[i + 1][j - 1].color.R * (0) +
								aux.M[i + 1][j].color.R * (-1) +
								aux.M[i + 1][j + 1].color.R * (0));
				(*img).M[i][j].color.G = clamp(aux.M[i - 1][j - 1].color.G *
											   (0) +
								aux.M[i - 1][j].color.G * (-1) +
								aux.M[i - 1][j + 1].color.G * (0) +
								aux.M[i][j - 1].color.G * (-1) +
								aux.M[i][j].color.G * (5) +
								aux.M[i][j + 1].color.G * (-1) +
								aux.M[i + 1][j - 1].color.G * (0) +
								aux.M[i + 1][j].color.G * (-1) +
								aux.M[i + 1][j + 1].color.G * (0));
				(*img).M[i][j].color.B = clamp(aux.M[i - 1][j - 1].color.B *
											   (0) +
								aux.M[i - 1][j].color.B * (-1) +
								aux.M[i - 1][j + 1].color.B * (0) +
								aux.M[i][j - 1].color.B * (-1) +
								aux.M[i][j].color.B * (5) +
								aux.M[i][j + 1].color.B * (-1) +
								aux.M[i + 1][j - 1].color.B * (0) +
								aux.M[i + 1][j].color.B * (-1) +
								aux.M[i + 1][j + 1].color.B * (0));
}

void blur(struct imagine *img, struct imagine aux, int i, int j)
{
	(*img).M[i][j].color.R =
				round(1.0 / 9 * (aux.M[i - 1][j - 1].color.R * (1) +
								aux.M[i - 1][j].color.R * (1) +
								aux.M[i - 1][j + 1].color.R * (1) +
								aux.M[i][j - 1].color.R * (1) +
								aux.M[i][j].color.R * (1) +
								aux.M[i][j + 1].color.R * (1) +
								aux.M[i + 1][j - 1].color.R * (1) +
								aux.M[i + 1][j].color.R * (1) +
								aux.M[i + 1][j + 1].color.R * (1)));
				(*img).M[i][j].color.G =
				round(1.0 / 9 * (aux.M[i - 1][j - 1].color.G * (1) +
								aux.M[i - 1][j].color.G * (1) +
								aux.M[i - 1][j + 1].color.G * (1) +
								aux.M[i][j - 1].color.G * (1) +
								aux.M[i][j].color.G * (1) +
								aux.M[i][j + 1].color.G * (1) +
								aux.M[i + 1][j - 1].color.G * (1) +
								aux.M[i + 1][j].color.G * (1) +
								aux.M[i + 1][j + 1].color.G * (1)));
				(*img).M[i][j].color.B =
				round(1.0 / 9 * (aux.M[i - 1][j - 1].color.B * (1) +
								aux.M[i - 1][j].color.B * (1) +
								aux.M[i - 1][j + 1].color.B * (1) +
								aux.M[i][j - 1].color.B * (1) +
								aux.M[i][j].color.B * (1) +
								aux.M[i][j + 1].color.B * (1) +
								aux.M[i + 1][j - 1].color.B * (1) +
								aux.M[i + 1][j].color.B * (1) +
								aux.M[i + 1][j + 1].color.B * (1)));
}

void APPLY(char *comanda, struct imagine *img, int x1, int x2, int y1, int y2,
		   int height, int width, char P)
{
	struct imagine aux;
	if (x1 - 1 < 0)
		x1++;
	if (x2 + 1 >= width)
		x2--;
	if (y1 - 1 < 0)
		y1++;
	if (y2 + 1 >= height)
		y2--;
	char parametru[256];
	copy_struct(&(*img), &aux, (*img).height, (*img).width);
	strcpy(parametru, comanda + 6);
	if ((*img).height == 0 || (*img).width == 0) {
		printf("No image loaded\n");
	} else if (strlen(comanda) == 5 || strlen(comanda) == 6) {
		printf("Invalid command\n");
	} else if (P == '2' || P == '5') {
		printf("Easy, Charlie Chaplin\n");
	} else if (!strcmp(parametru, "EDGE")) {
		//apply edge
		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				edge(&(*img), aux, i, j);
		printf("APPLY EDGE done\n");
	} else if (!strcmp(parametru, "SHARPEN")) {
		//apply sharpen
		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				sharpen(&(*img), aux, i, j);
		printf("APPLY SHARPEN done\n");
	} else if (!strcmp(parametru, "BLUR")) {
		//apply blur
		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++)
				blur(&(*img), aux, i, j);
		printf("APPLY BLUR done\n");
	} else if (!strcmp(parametru, "GAUSSIAN_BLUR")) {
		//apply blur
		for (int i = y1; i < y2; i++)
			for (int j = x1; j < x2; j++) {
				(*img).M[i][j].color.R =
				round(1.0 / 16 * (aux.M[i - 1][j - 1].color.R * (1) +
								aux.M[i - 1][j].color.R * (2) +
								aux.M[i - 1][j + 1].color.R * (1) +
								aux.M[i][j - 1].color.R * (2) +
								aux.M[i][j].color.R * (4) +
								aux.M[i][j + 1].color.R * (2) +
								aux.M[i + 1][j - 1].color.R * (1) +
								aux.M[i + 1][j].color.R * (2) +
								aux.M[i + 1][j + 1].color.R * (1)));
				(*img).M[i][j].color.G =
				round(1.0 / 16 * (aux.M[i - 1][j - 1].color.G * (1) +
								aux.M[i - 1][j].color.G * (2) +
								aux.M[i - 1][j + 1].color.G * (1) +
								aux.M[i][j - 1].color.G * (2) +
								aux.M[i][j].color.G * (4) +
								aux.M[i][j + 1].color.G * (2) +
								aux.M[i + 1][j - 1].color.G * (1) +
								aux.M[i + 1][j].color.G * (2) +
								aux.M[i + 1][j + 1].color.G * (1)));
				(*img).M[i][j].color.B =
				round(1.0 / 16 * (aux.M[i - 1][j - 1].color.B * (1) +
								aux.M[i - 1][j].color.B * (2) +
								aux.M[i - 1][j + 1].color.B * (1) +
								aux.M[i][j - 1].color.B * (2) +
								aux.M[i][j].color.B * (4) +
								aux.M[i][j + 1].color.B * (2) +
								aux.M[i + 1][j - 1].color.B * (1) +
								aux.M[i + 1][j].color.B * (2) +
								aux.M[i + 1][j + 1].color.B * (1)));
			}
		printf("APPLY GAUSSIAN_BLUR done\n");
	} else {
		printf("APPLY parameter invalid\n");
	}
	free_image(&aux, aux.height);
}

void patrat(struct imagine *img, char *unghi, int *x1, int *x2, int *y1,
			int *y2)
{
	struct imagine aux;
	copy_struct(&(*img), &aux, (*img).height, (*img).width);
	if (!strcmp(unghi, "-90")) {
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				(*img).M[i][j] = aux.M[*y1 + (j - *x1)][*x2 - (i - *y1) - 1];
		printf("Rotated -90\n");
	} else if (!strcmp(unghi, "+90") || !strcmp(unghi, "90")) {
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				(*img).M[i][j] = aux.M[*y2 - 1 - (i - *y1)][*x2 - 1 -
				(j - *x1)];
		//free aux
		free_image(&aux, aux.height);
		copy_struct(&(*img), &aux, (*img).height, (*img).width);
		//
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				(*img).M[i][j] = aux.M[*y1 + (j - *x1)][*x2 - (i - *y1) - 1];
		if (!strcmp(unghi, "+90"))
			printf("Rotated +90\n");
		else
			printf("Rotated 90\n");
	} else if (!strcmp(unghi, "-180")) {
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				(*img).M[i][j] = aux.M[*y2 - 1 - (i - *y1)][*x2 - 1 -
				(j - *x1)];
		printf("Rotated -180\n");
	} else if (!strcmp(unghi, "+180") || !strcmp(unghi, "180")) {
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				(*img).M[i][j] = aux.M[*y2 - 1 - (i - *y1)][*x2 - 1 -
				(j - *x1)];
		if (!strcmp(unghi, "+180"))
			printf("Rotated +180\n");
		else
			printf("Rotated 180\n");
	} else if (!strcmp(unghi, "-270")) {
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				(*img).M[i][j] = aux.M[*y2 - 1 - (i - *y1)][*x2 - 1 -
				(j - *x1)];
		//free aux
		free_image(&aux, aux.height);
		copy_struct(&(*img), &aux, (*img).height, (*img).width);
		//
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				(*img).M[i][j] = aux.M[*y1 + (j - *x1)][*x2 - (i - *y1) - 1];
		printf("Rotated -270\n");
	} else if (!strcmp(unghi, "+270") || !strcmp(unghi, "270")) {
		for (int i = *y1; i < *y2; i++)
			for (int j = *x1; j < *x2; j++)
				(*img).M[i][j] = aux.M[*y1 + (j - *x1)][*x2 - (i - *y1) - 1];
		if (!strcmp(unghi, "+270"))
			printf("Rotated +270\n");
		else
			printf("Rotated 270\n");
	} else if (!strcmp(unghi, "-360")) {
		printf("Rotated -360\n");
	} else if (!strcmp(unghi, "+360") || !strcmp(unghi, "360")) {
		if (!strcmp(unghi, "+360"))
			printf("Rotated +360\n");
		else
			printf("Rotated 360\n");
	} else if (!strcmp(unghi, "0")) {
		printf("Rotated 0\n");
	}
	//free aux
	free_image(&aux, aux.height);
}

void aloc_img(struct imagine *img, struct imagine aux)
{
	img->M = (union pixel **)calloc(aux.width, sizeof(union pixel *));
	if (!img->M) {
		printf("Could not access memory\n");
		exit(-11);
	}
	for (int i = 0; i < aux.width; i++) {
		img->M[i] = (union pixel *)calloc(aux.height, sizeof(union pixel));
		if (!img->M[i]) {
			printf("Could not access memory\n");
			exit(-11);
		}
	}
	img->height = aux.width;
	img->width = aux.height;
}

void toata_img(struct imagine *img, char *unghi, int *x2, int *y2)
{
	struct imagine aux;
	copy_struct(&(*img), &aux, img->height, img->width);
	if (!strcmp(unghi, "-90")) {
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				(*img).M[i][j] = aux.M[img->height - i - 1][img->width - j - 1];
		free_image(&aux, aux.height);
		copy_struct(&(*img), &aux, img->height, img->width);
		free_image(&(*img), img->height);
		aloc_img(&(*img), aux);
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				(*img).M[i][j] = aux.M[img->width - j - 1][i];
		printf("Rotated -90\n");
	} else if (!strcmp(unghi, "+90") || !strcmp(unghi, "90")) {
		free_image(&(*img), img->height);
		aloc_img(&(*img), aux);
		img->height = aux.width;
		img->width = aux.height;
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				(*img).M[i][j] = aux.M[img->width - j - 1][i];
		if (!strcmp(unghi, "+90"))
			printf("Rotated +90\n");
		else
			printf("Rotated 90\n");
	} else if (!strcmp(unghi, "-180")) {
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				(*img).M[i][j] = aux.M[img->height - i - 1][img->width - j - 1];
		printf("Rotated -180\n");
	} else if (!strcmp(unghi, "+180") || !strcmp(unghi, "180")) {
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				(*img).M[i][j] = aux.M[img->height - i - 1][img->width - j - 1];
		if (!strcmp(unghi, "+180"))
			printf("Rotated +180\n");
		else
			printf("Rotated 180\n");
	} else if (!strcmp(unghi, "-270")) {
		free_image(&(*img), img->height);
		aloc_img(&(*img), aux);
		img->height = aux.width;
		img->width = aux.height;
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				(*img).M[i][j] = aux.M[img->width - j - 1][i];
		printf("Rotated -270\n");
	} else if (!strcmp(unghi, "+270") || !strcmp(unghi, "270")) {
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				(*img).M[i][j] = aux.M[img->height - i - 1][img->width - j - 1];
		free_image(&aux, aux.height);
		copy_struct(&(*img), &aux, img->height, img->width);
		free_image(&(*img), img->height);
		aloc_img(&(*img), aux);
		img->height = aux.width;
		img->width = aux.height;
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				(*img).M[i][j] = aux.M[img->width - j - 1][i];
		if (!strcmp(unghi, "+270"))
			printf("Rotated +270\n");
		else
			printf("Rotated 270\n");
	} else if (!strcmp(unghi, "-360")) {
		printf("Rotated -360\n");
	} else if (!strcmp(unghi, "+360") || !strcmp(unghi, "360")) {
		if (!strcmp(unghi, "+360"))
			printf("Rotated +360\n");
		else
			printf("Rotated 360\n");
	} else if (!strcmp(unghi, "0")) {
		printf("Rotated 0\n");
	}
	free_image(&aux, aux.height);
	*x2 = img->width;
	*y2 = img->height;

}

void ROTATE(char *comanda, int *x1, int *x2, int *y1, int *y2,
			struct imagine *img)
{
	char unghi[256];
	strcpy(unghi, comanda + 7);
	if ((*img).height == 0 || (*img).width == 0) {
		printf("No image loaded\n");
	} else if (!(!strcmp(unghi, "-90") || !strcmp(unghi, "+90") ||
		!strcmp(unghi, "-180") || !strcmp(unghi, "+180") ||
		!strcmp(unghi, "-270") || !strcmp(unghi, "+270") ||
		!strcmp(unghi, "+360") || !strcmp(unghi, "-360") ||
		!strcmp(unghi, "90") || !strcmp(unghi, "180") ||
		!strcmp(unghi, "270") || !strcmp(unghi, "360") ||
		!strcmp(unghi, "0"))) {
		printf("Unsupported rotation angle\n");
	} else if (*y2 - *y1 != *x2 - *x1 && (*x1 != 0 && *x2 != img->width &&
			   *y1 != 0 && *y2 != img->height)) {
		printf("The selection must be square\n");
	} else {
		if (!(*x1 == 0 && *x2 == img->width && *y1 == 0 && *y2 == img->height))
			patrat(&(*img), unghi, &(*x1), &(*x2), &(*y1), &(*y2));
		else
			toata_img(&(*img), unghi, &(*x2), &(*y2));
	}
}

void HISTOGRAM(struct imagine img, char *comanda, char P)
{
	int ap[257], i, j, x, y;
	//initializare cu 0
	for (int i = 0; i < 256; i++)
		ap[i] = 0;
	if (img.height == 0 || img.width == 0) {
		printf("No image loaded\n");
	} else if (strlen(comanda) == 9) {
		printf("Invalid command\n");
	} else if (P == '3' || P == '6') {
		printf("Black and white image needed\n");
	} else {
		//formare vector de aparitii
		for (int i = 0; i < img.height; i++)
			for (int j = 0; j < img.width; j++)
				ap[img.M[i][j].tone.intensity]++;
		//
		char valori[256];
		strcpy(valori, comanda + 10);
		i = 0;
		j = 0;
		x = 0;
		y = 0;
		if (!strchr(valori, ' ') || strchr(strchr(valori, ' ') + 1, ' ')) {
			printf("Invalid command\n");
		} else {
			while (valori[j] != ' ')
				j++;
			while (i != j)
				x = x * 10 + (valori[i++] - '0');
			i = j + 1;
			j = strlen(valori);
			while (i != j)
				y = y * 10 + (valori[i++] - '0');
			//
			int interval = 256 / y, bin[256], max;
			max = 0;
			for (int i = 0; i < y; i++) {
				bin[i] = 0;
				for (int j = 0; j < interval; j++)
					bin[i] += ap[i * interval + j];
				if (bin[i] > max)
					max = bin[i];
			}
			for (int i = 0; i < y; i++) {
				printf("%d ", bin[i] * x / max);
				printf("\t");
				printf("|");
				printf("\t");
				for (int j = 0; j < bin[i] * x / max; j++)
					printf("*");
				printf("\n");
			}
		}
	}
}

void EQUALIZE(char P, struct imagine *img)
{
	if (P == '3' || P == '6') {
		printf("Black and white image needed\n");
	} else if ((*img).height == 0 || (*img).width == 0) {
		printf("No image loaded\n");
	} else {
		int ap[256], sum;
		for (int i = 0; i < 256; i++)
			ap[i] = 0;
		for (int i = 0; i < (*img).height; i++)
			for (int j = 0; j < (*img).width; j++)
				ap[(*img).M[i][j].tone.intensity]++;

		for (int i = 0; i < (*img).height; i++)
			for (int j = 0; j < (*img).width; j++) {
				sum = 0;
				for (int p = 0; p <= (*img).M[i][j].tone.intensity; p++)
					sum += ap[p];

				double rez = 255.0 * sum / ((*img).height * (*img).width);
				(*img).M[i][j].tone.intensity = round(clamp(rez));
			}
		printf("Equalize done\n");
	}
}

void assign(int *h, int *x1, int *x2, int *y1, int *y2, int *height,
			int *wid, int *test)
{
	*h = 0;
	*x1 = 0;
	*x2 = 0;
	*y1 = 0;
	*y2 = 0;
	*height = 0;
	*wid = 0;
	*test = 1;
}

int main(void)
{
	char comanda[257], P, nume_fisier[256];
	int x1, x2, y1, y2, h, is_ascii, distanta, test;
	assign(&h, &x1, &x2, &y1, &y2, &img.height, &img.width, &test);
	fgets(comanda, 256, stdin);
	comanda[strlen(comanda) - 1] = 0;
	while (test) {
		if (strncmp(comanda, "LOAD", 4) == 0) {
			strcpy(nume_fisier, comanda + 5);
			FILE *f = fopen(nume_fisier, "rw");
			if (!f) {
				printf("Failed to load %s\n", nume_fisier);
				if (img.height != 0 && img.width != 0)
					free_image(&img, img.height);
			} else {
				if (img.height != 0)
					free_image(&img, img.height);
				fseek(f, 1, SEEK_SET);
				P = fgetc(f);
				if (P < '4')
					is_ascii = 1;
				else
					is_ascii = 0;
				citeste_antet(P, f, &img.height, &img.width, &h);
				distanta = ftell(f);
				x1 = 0;
				y1 = 0;
				x2 = img.width;
				y2 = img.height;
				if (is_ascii) {
					if (P == '2') {
						load_P2(img.height, img.width, nume_fisier, f, &img);
						fclose(f);
					} else if (P == '3') {
						load_P3(img.height, img.width, nume_fisier, f, &img);
						fclose(f);
					}
				} else {
					fclose(f);
					FILE *f = fopen(nume_fisier, "rwb");
					if (P == '5') {
						load_P5(img.height, img.width, nume_fisier, f, &img,
								distanta);
						fclose(f);
					} else if (P == '6') {
						load_P6(img.height, img.width, nume_fisier, f, &img,
								distanta);
						fclose(f);
					}
				}
			}
		} else if (!strncmp(comanda, "SELECT ALL", 10)) {
			select_all(img.height, img.width, &x1, &x2, &y1, &y2);
		} else if (!strncmp(comanda, "SELECT", 6)) {
			SELECT(&x1, &x2, &y1, &y2, img.height, img.width, comanda);
		} else if (!strncmp(comanda, "HISTOGRAM", 9)) {
			HISTOGRAM(img, comanda, P);
		} else if (!strcmp(comanda, "EQUALIZE")) {
			EQUALIZE(P, &img);
		} else if (!strncmp(comanda, "ROTATE", 6)) {
			ROTATE(comanda, &x1, &x2, &y1, &y2, &img);
		} else if (!strcmp(comanda, "CROP")) {
			CROP(&img.height, &img.width, &x1, &x2, &y1, &y2, &img);
		} else if (!strncmp(comanda, "APPLY", 5)) {
			APPLY(comanda, &img, x1, x2, y1, y2, img.height, img.width, P);
		} else if (!strncmp(comanda, "SAVE", 4)) {
			SAVE(comanda, P, img, h);
		} else if (!strcmp(comanda, "EXIT")) {
			if (img.height == 0 || img.width == 0)
				printf("No image loaded\n");
			else
				free_image(&img, img.height);
			test = 0;
		} else {
			printf("Invalid command\n");
		}
		fgets(comanda, 256, stdin);
		if (strcmp(comanda, "EXIT"))
			comanda[strlen(comanda) - 1] = 0;
	}
}
