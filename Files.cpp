#include <bits/stdc++.h>
#include "Files.hpp"

double **create_matriz_cero(int n, int m){
    double **matrix;
	matrix = (double **) calloc(n,sizeof(double*));

	for(int i = 0; i < n; i++){
		matrix[i] = (double *) calloc (m,sizeof(double));
	}

	return matrix;
}

double *create_vector_cero(int n){
    double *vector;
	vector = (double *) calloc (n, sizeof(double));
	return vector;
}

void update_PGM(int h, int m, int rows, int cols, int max_scale, double **A) {
	string filename = "ORL Face Database/s" + to_string(m+1) + "/" + to_string(h+1) + "_c.pgm";
	
	ifstream file(filename);

	if (file.is_open() == 0){
		cerr << "No existe el archivo." <<endl;
		exit(-1);
	}

	string line; 
	string word; 

	getline(file, line);
	if (line.compare("P2") != 0){
		cout << "Formato no válido." << endl;
	}
						
	getline(file, line);
	// Skip Comments
	while (line[0] == '#'){ 
		getline(file, line);
	}
	// Check dimentions
	stringstream ss(line);  
		
	getline(ss,word,' ');
	int _cols = stoi(word); 
	if (_cols != cols) {
		cout << "Dimentions corrupted." << endl;
		exit(-1);
	}
		
	getline(ss,word,' ');     
	int _rows = stoi(word);

	if (_rows != rows) {
		cout << "Dimentions corrupted." << endl;
			exit(-1);
	}
	
	int _max_scale;
	file >> _max_scale;

	if (_max_scale != max_scale) {
		cout << "Gray scale corrupted." << endl;
		exit(-1);
	}

	// Read data
	for (int i = 0; i < rows*cols; i++) {
		file >> A[m+40*h][i];
		// normalize data
		A[m+40*h][i] = A[m+40*h][i]/max_scale;
	}
			
	file.close();
}

void update_dataset(int images_per_person, int max_index, int rows, int cols, int max_scale, double **A) {
	// Images per person
	for (int h = 0; h < images_per_person; h++) {	
		// Persons in range [1, max_index]
		for (int m = 0; m < max_index; m++) {
			update_PGM(h, m, rows, cols, max_scale, A);
		}
	}

}

void update_PGMTest(int h, int m, int rows, int cols, int max_scale, double *A){
	string filename = "ORL Face Database/s" + to_string(m+1) + "/" + to_string(h+1) + "_c.pgm";
	
	ifstream file(filename);

	if (file.is_open() == 0){
		cerr << "No existe el archivo." <<endl;
		exit(-1);
	}

	string line; 
	string word; 

	getline(file, line);
	if (line.compare("P2") != 0){
		cout << "Formato no válido." << endl;
	}
						
	getline(file, line);
	// Skip Comments
	while (line[0] == '#'){ 
		getline(file, line);
	}
	// Check dimentions
	stringstream ss(line);  
		
	getline(ss,word,' ');
	int _cols = stoi(word); 
	if (_cols != cols) {
		cout << "Dimentions corrupted." << endl;
		exit(-1);
	}
		
	getline(ss,word,' ');     
	int _rows = stoi(word);

	if (_rows != rows) {
		cout << "Dimentions corrupted." << endl;
		exit(-1);
	}
	
	int _max_scale;

	file >> _max_scale;
	if (_max_scale != max_scale) {
		cout << "Gray scale corrupted." << endl;
		exit(-1);
	}

	// Read data
	for (int i = 0; i < rows*cols; i++) {
		file >> A[i];
		// normalize data
		A[i] = A[i]/(double) max_scale;
	}
			
	file.close();
}

void write_average_face(int rows, int cols, int max_scale, double *A) {
	string filename = "Out/average_face.pgm";
	
	ofstream file(filename);

	file << "P2" << endl;

	file << "# Average contibution" << endl;

	file << cols << " " << rows << endl;				

	file << max_scale << endl;

	int pivot = 0;
	// Read data
	for (int i = 0; i < rows*cols; i++) {
		pivot = (int) max_scale * A[i];
		file << pivot <<endl;
	}
			
	file.close();
}

void write_PGM(int index, int rows, int cols, int max_scale, double **A) {
	string filename = "Out/eigenface_" + to_string(index) + ".pgm";
	
	ofstream file(filename);

	file << "P2" << endl;

	file << "# Face with average contibution" << endl;

	file << cols << " " << rows << endl;				

	file << max_scale << endl;

	int pivot = 0;
	// Read data
	for (int i = 0; i < rows*cols; i++) {
		pivot = max_scale *(A[index][i]+1)/2;
		file << pivot <<endl;
	}
			
	file.close();
}

void write_Individual_PGM(int index, int person, int rows, int cols, int max_scale, double *A) {
	string filename = "Out/s_" + to_string(person+1) + "_" + to_string(index+1) + ".pgm";
	
	ofstream file(filename);

	file << "P2" << endl;

	file << "# Face with average contibution" << endl;

	file << cols << " " << rows << endl;				

	file << max_scale << endl;

	int pivot = 0;
	// Read data
	for (int i = 0; i < rows*cols; i++) {
		pivot = (int) A[i];
		file << pivot <<endl;
	}
			
	file.close();
}

void write_eigenfaces(int K, int rows, int cols, int max_scale, double **A) {
	// Images per person
	for (int h = 0; h < K; h++) {	
			write_PGM(h, rows, cols, max_scale,  A);
	}
}

void write_vector(int n, double *vector, char *vecname){
	FILE * vptr = fopen(vecname, "w");

	fprintf(vptr, "%d %d\n", n, 1);
	for(int i = 0; i < n-1; i++){
		fprintf(vptr, "%lf\n", vector[i]);
	}
	fprintf(vptr, "%lf", vector[n-1]);
	
	fclose(vptr);
	printf("Hurra! Se escribió vector en: %s\n", vecname);

}

void write_matrix(int n,int m, double **matrix, char *matrix_name){
	FILE * vptr = fopen(matrix_name, "w");
	fprintf(vptr, "%d %d\n", n, m);
	
	for(int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (j == m-1) {
                fprintf(vptr, "%lf\n", matrix[i][j]);
            }
            else{
                fprintf(vptr, "%lf ", matrix[i][j]);
            }
        }
	}
	
	fclose(vptr);
	printf("Hurra! Se escribió matriz en: %s\n", matrix_name);

}

void freeMatrix(int n, double ** matrix) {
    int i;
    for (i = 0; i < n; i++) {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;
}

int *set_training_index (int images_per_person, int end_index, int M) {
	 int *A_index = (int *) calloc (M, sizeof(int));
    // Images per person
	for (int h = 0; h < images_per_person; h++) {	
		// Persons in range [1, max_index]
		for (int m = 0; m < end_index; m++) {
			A_index[m+40*h] = m+1;
		}
	}
	return A_index;
}

void write_eigengraph(int size, double *x, string filename){
	ofstream file(filename);

	for (int i = 0; i < size; i++) {
		file << i+1 << " " << x[i] << endl;
	}

	file.close();
}