// MegaShow
#include "Matrix.h"

Matrix::Matrix(string str, int h, int w, int** p){
	name = str;
	width = w;
	height = h;
	param = new int*[height];
	for(int i = 0; i < height; i++){
		param[i] = new int[width];
		for(int j = 0; j < width; j++)
			param[i][j] = p[i][j];
	}
}
        
Matrix::Matrix(const Matrix & m){
	name = m.name;
	width = m.width;
	height = m.height;
	param = new int*[height];
	for(int i = 0; i < height; i++){
		param[i] = new int[width];
		for(int j = 0; j < width; j++)
			param[i][j] = m.param[i][j];
	}
}
        
Matrix::~Matrix(){
	for(int i = 0; i < height; i++)
		delete [] param[i];
	delete [] param;
}
                
bool Matrix::operator ==(const Matrix& m){
	if(width != m.width || height != m.height)
		return false;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(param[i][j] != m.param[i][j])
				return false;
		}
	}
	return true;
}
        
bool Matrix::operator !=(const Matrix& m){
	Matrix a(name, width, height, param);
	return !(a == m);
}

void Matrix::operator +=(const Matrix& m){
	if(height != m.height || width != m.width){
		cout << "invalid addition." << endl;
		return;
	}
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			param[i][j] += m.param[i][j];
		}
	}
}

void Matrix::operator -=(const Matrix& m){
	if(height != m.height || width != m.width){
		cout << "invalid substraction." << endl;
		return;
	}
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			param[i][j] -= m.param[i][j];
		}
	}
}

Matrix Matrix::operator *(const Matrix& m){
	if(width != m.height){
		cout << "invalid multiplication." << endl;
		return Matrix();
	}
	int** arr;
	arr = new int*[height];
	for(int i = 0; i < height; i++)
		arr[i] = new int[m.width];
	for(int i = 0; i < height; i++){
		for(int j = 0; j < m.width; j++){
			arr[i][j] = 0;
			for(int k = 0; k < width; k++){
				arr[i][j] += (param[i][k] * m.param[k][j]);
			}
		}
	}
	Matrix tmp("newMat", height, m.width, arr);
	for(int i = 0; i < height; i++)
		delete [] arr[i];
	delete [] arr;
	return tmp;
}