//Pham Thi Ngoc Lan
//Mssv: 20237453 
#include <iostream >
#include <conio.h>
#include <stdlib.h>
#include <windows.h> 
#include <cmath>
#include <fstream>
using namespace std;
const int MAX=100; 

void swap(double &a, double &b);
double nhapSo();
int nhapSoNguyen();
void insothuc(double x, int pre, ofstream &fout);
void nhapmatran(int row, int column, double A[MAX][MAX]);
void inmatran(int row, int column, double A[MAX][2*MAX],int pre,ofstream &fout);
void matrantamgiac(int m, int n, double A[MAX][2*MAX], int &count,int pre,ofstream &fout);
void tinhdinhthuc(int m,double A[MAX][2*MAX],int pre,ofstream &fout);
void matranbosung(int m, int n, int p, double A[MAX][MAX], double b[MAX][MAX], double Ab[MAX][2*MAX]);
int tinhrank(int m, int n, double A[MAX][2*MAX], int pre,ofstream &fout);
int ketLuanNghiem(int m, int n, int p, double A[MAX][MAX], double b[MAX][MAX], int pre,ofstream &fout);
void gauss(int m, int n, int p, double A[MAX][MAX], double b[MAX][MAX], double X[MAX][MAX], int pre,ofstream &fout);
void gaussjordan(int m, int n, int p, double A[MAX][MAX], double b[MAX][MAX], int pre,ofstream &fout);
void docMatranTuFile(int &m, int &n, double A[MAX][MAX]);
void docHeTuFile(int& m, int &n, int &p, double A[MAX][MAX], double b[MAX][MAX]);
const char *menuChinh[] = {
    "Tinh dinh thuc",
    "Giai he phuong trinh Ax=b",
    "Thoat"
};
const int soMenuChinh = sizeof(menuChinh) / sizeof(menuChinh[0]);

const char *menuNhapDuLieu[] = {
    "Nhap tu ban phim",
    "Doc tu file"
};
const int soMenuNhapDuLieu = sizeof(menuNhapDuLieu) / sizeof(menuNhapDuLieu[0]);

const char *menuGiaiHe[] = {
    "Gauss",
    "Gauss-Jordan"
};
const int soMenuGiaiHe = sizeof(menuGiaiHe) / sizeof(menuGiaiHe[0]);
int menuDong(const char *options[], int size);

int main() {
    SetConsoleOutputCP(65001); 
    int m, n, p;
    double A[MAX][MAX], b[MAX][MAX], Ab[MAX][2*MAX], X[MAX][MAX], A1[MAX][2*MAX];
    int pre, count = 0;
    ofstream fout("matran.txt");

    while (true) {
        int chon = menuDong(menuChinh, soMenuChinh);
        if (chon == 0) {
            cout << "\n--- Tinh dinh thuc ma tran ---\n";
            fout << "\n--- Tinh dinh thuc ma tran ---\n";
            int nhap = menuDong(menuNhapDuLieu, soMenuNhapDuLieu);

            if (nhap == 0) {
            	fout << "Nguoi dung chon: Nhap ma tran bang tay\n";
                cout << "Nhap kich thuoc ma tran vuong: ";
                fout << "Nhap kich thuoc ma tran vuong: ";
                m = nhapSoNguyen();
                n = m;
                fout << "Kich thuoc: " << m << " x " << n << "\n";
                cout << "Nhap ma tran:\n";
                fout << "Nhap ma tran:\n";
                nhapmatran(m, m, A);
            } else {
                fout << "Nguoi dung chon: Doc ma tran tu file\n";
                docMatranTuFile(m, n, A);
                fout << "Kich thuoc doc tu file: " << m << " x " << n << "\n";
                if (m != n) {
                    cout << "Ma tran khong vuong. Khong the tinh dinh thuc.\n";
                    fout << "Ma tran khong vuong. Khong the tinh dinh thuc.\n";
                    continue;
                }
            }

            cout << "Nhap so chu so thap phan muon hien thi: ";
            fout << "Nhap so chu so thap phan muon hien thi: ";
            pre = nhapSoNguyen();
            fout << pre << "\n";

            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    A1[i][j] = A[i][j];

            matrantamgiac(m, m, A1, count, pre, fout);
            cout << "Ma tran tam giac:\n";
            fout << "Ma tran tam giac:\n";
            inmatran(m, m, A1, pre, fout);
            tinhdinhthuc(m, A1, pre, fout);
        } 
        else if (chon == 1) {
            cout << "\n--- Giai he phuong trinh Ax = b ---\n";
            fout << "\n--- Giai he phuong trinh Ax = b ---\n";
            int nhap = menuDong(menuNhapDuLieu, soMenuNhapDuLieu);

            if (nhap == 0) {
                fout << "Nguoi dung chon: Nhap du lieu bang tay\n";
                cout << "Nhap kich thuoc ma tran A (m x n):\n";
                fout << "Nhap kich thuoc ma tran A (m x n):\n";
                cout << "m = "; fout << "m = ";
				m = nhapSoNguyen();fout << m << "\n";
                cout << "n = ";  fout << "n = ";
				n = nhapSoNguyen(); fout << n << "\n";
                cout << "Nhap ma tran A:\n";
                fout << "Nhap ma tran A:\n";
                nhapmatran(m, n, A);
                cout << "Nhap so cot cua ma tran b: ";
                fout << "Nhap so cot cua ma tran b: ";
                p = nhapSoNguyen();fout << p << "\n";
                cout << "Nhap ma tran b:\n";
                fout << "Nhap ma tran b:\n";
                nhapmatran(m, p, b);
            } else {
            	fout << "Nguoi dung chon: Doc du lieu tu file\n";
                docHeTuFile(m, n, p, A, b); 
                fout << "Kich thuoc ma tran A: " << m << " x " << n << "\n";
                fout << "So cot cua b: " << p << "\n";
            }

            cout << "Nhap so chu so thap phan muon hien thi: ";
            fout << "Nhap so chu so thap phan muon hien thi: ";
            pre = nhapSoNguyen();
            fout << pre << "\n";
            int phuongPhap = menuDong(menuGiaiHe, soMenuGiaiHe);
             fout << "Phuong phap giai he: " << (phuongPhap == 0 ? "Gauss\n" : "Gauss-Jordan\n");
            matranbosung(m, n, p, A, b, Ab);
            fout << "Ma tran bo sung:\n";
            cout << "Ma tran bo sung:\n";
            inmatran(m, n + p, Ab, pre, fout);

            if (phuongPhap == 0) {
                cout << "-> Su dung phuong phap Gauss.\n";
                fout << "-> Su dung phuong phap Gauss.\n";
                gauss(m, n, p, A, b, X, pre, fout);
            } else {
                cout << "-> Su dung phuong phap Gauss-Jordan.\n";
                fout << "-> Su dung phuong phap Gauss-Jordan.\n";
                gaussjordan(m, n, p, A, b, pre, fout);
            }
        } 
        else if (chon == 2) {
            cout << "-> Thoat chuong trinh.\n";
            break;
        }

        cout << "\nNhan phim bat ky de tiep tuc...";
        cin.ignore();
        cin.get();
    }

    fout.close();
    cout << "Toan bo qua trinh da duoc luu vao file Matran.txt\n";
    return 0;
}

void swap(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}

double nhapSo() {
    double x;
    while (true) {
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n'); 
            cout << "Gia tri khong hop le. Vui long nhap lai: ";
        } else {
            return x; 
        }
    }
}


int nhapSoNguyen() {
    int x;
    while (true) {
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Gia tri khong hop le. Vui long nhap lai: ";
        } else {
            cin.ignore(10000, '\n');
            return x;
        }
    }
}

void insothuc(double x, int pre, ofstream &fout) {
    double rounded = round(x * pow(10, pre)) / pow(10, pre);
    int nguyen = (int)rounded;
    cout << nguyen << ".";
    fout << nguyen << ".";
    double thapphan = rounded - nguyen;
    if (thapphan < 0) thapphan = -thapphan;
    for (int i = 0; i < pre; i++) {
        thapphan *= 10;
        int digit = (int)thapphan;
        cout << digit;
        fout << digit;
        thapphan -= digit;
    }
    cout << "\t";
    fout << "\t";
}
void nhapmatran(int row, int column, double A[MAX][MAX]){
	int i,j; 
	for( i=0; i<row;i++){
		for( j=0; j<column;j++){
		A[i][j] = nhapSo();	
		}
	}
} 

void inmatran(int row, int column, double A[MAX][2*MAX],int pre,ofstream &fout){
	int i,j; 
	for( i=0; i<row;i++){
		for( j=0; j<column;j++){
			insothuc(A[i][j],pre,fout);
		}
		cout<<endl;
		fout<<endl;
	}
} 

void matrantamgiac(int m, int n, double A[MAX][2*MAX], int &count,int pre,ofstream &fout) {
    count = 0;
    int i, j, k;
    int pivot;
    double factor;

    for (i = 0; i < m; i++) {
        pivot = i;
     
        for (j = i + 1; j < m; j++) {
            if (fabs(A[j][i]) > fabs(A[pivot][i]))
                pivot = j;
        }

        if (fabs(A[pivot][i]) < 1e-12) {
            continue;
        }
 
        if (pivot != i) {
            for (k = 0; k < n; k++) {
                swap(A[i][k], A[pivot][k]);
            }
        }
       
        for (j = i + 1; j < m; j++) {
            factor = A[j][i] / A[i][i];
            if (fabs(factor) < 1e-12) continue; 
            for (k = 0; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            count++;
        }
    }
}


void tinhdinhthuc(int m,double A[MAX][2*MAX],int pre,ofstream &fout){
	double B[MAX][2*MAX];
	double det=1;
	int i,j; 
	int count=0;
    for ( i = 0; i < m; i++)
        for ( j = 0; j < m; j++)
            B[i][j] = A[i][j];
    matrantamgiac(m,m,B, count,pre,fout);
    
    for(i=0;i<m;i++)
    det*=B[i][i];
    if (count%2==0)
    det=det;
    else det=-det;
    cout<<" Dinh thuc cua ma tran la ";
    fout<<" Dinh thuc cua ma tran la ";
    insothuc(det,pre,fout);
}

void matranbosung(int m, int n, int p, double A[MAX][MAX], double b[MAX][MAX], double Ab[MAX][2*MAX]) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            Ab[i][j] = A[i][j];
        }
        for (j = 0; j < p; j++) {
            Ab[i][n + j] = b[i][j];
        }
    }
}

int tinhrank(int m, int n, double A[MAX][2*MAX], int pre,ofstream &fout) {
    double B[MAX][2*MAX];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];
    int count = 0;
    matrantamgiac(m, n, B, count, pre,fout);
    int rank = 0;
    for (int i = 0; i < m; i++) {
        bool dongKhac0 = false;
        for (int j = 0; j < n; j++) {
            if (fabs(B[i][j]) > 1e-9) {
                dongKhac0 = true;
                break;
            }
        }
        if (dongKhac0) rank++;
    }
    return rank;
}

int ketLuanNghiem(int m, int n, int p, double A[MAX][MAX], double b[MAX][MAX], int pre,ofstream &fout) {
    double Ab[MAX][2 * MAX], A1[MAX][2 * MAX];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            A1[i][j] = A[i][j];
    int rankA = tinhrank(m, n, A1, pre,fout);
    matranbosung(m, n, p, A, b, Ab);
    int rankAb = tinhrank(m, n + p, Ab, pre,fout);
    if (rankA < rankAb) {
        return 0; 
    } 
    if (rankA == rankAb && rankA == n) {
        return 1;  
    } 
    else return 2;  
}

void gauss(int m, int n, int p, double A[MAX][MAX], double b[MAX][MAX], double X[MAX][MAX], int pre,ofstream &fout) {
    int i, j, k;
    int count = 0;
    double Ab[MAX][2*MAX];
    int kq = ketLuanNghiem(m, n, p, A, b, pre,fout);
    matranbosung(m, n, p,A,b,Ab); 
    cout << endl; 
    fout << endl;
    cout << "Qua trinh thuan:\n\n";
    fout << "Qua trinh thuan:\n\n";
    matrantamgiac(m, n + p, Ab, count, pre,fout);
    inmatran(m,n+p,Ab,pre,fout) ;
    cout << endl; 
    fout << endl; 
    cout << "Qua trinh nghich:\n\n";
    fout << "Qua trinh nghich:\n\n";
    if (kq == 0) {
        cout << "He phuong trinh vo nghiem." << endl;
        fout << "He phuong trinh vo nghiem." << endl;
    }
    else if (kq == 1) {
        cout << "He phuong trinh co nghiem duy nhat." << endl;
		fout << "He phuong trinh co nghiem duy nhat." << endl;		
        for (k = 0; k < p; k++) {          
            for (i = n - 1; i >= 0; i--) {  
                X[i][k] = Ab[i][n + k];
                for (j = i + 1; j < n; j++) {
                    X[i][k] -= Ab[i][j] * X[j][k];
                }
                X[i][k] /= Ab[i][i];
            }
        }
        cout << "Nghiem cua he phuong trinh:\n";
        fout << "Nghiem cua he phuong trinh:\n";
        for (k = 0; k < p; k++) {
            cout << "Nghiem thu " << k + 1 << ": ";
            fout << "Nghiem thu " << k + 1 << ": ";
            for (i = 0; i < n; i++) {
                insothuc(X[i][k], pre,fout);
                cout << "\t";
                fout << "\t";
            }
            cout << endl;
            fout << endl;
        }
    }
    else if (kq == 2) {
        cout << "He phuong trinh co vo so nghiem.\n";
        fout << "He phuong trinh co vo so nghiem.\n";

        int index[MAX]; 
        for (int i = 0; i < n; ++i) index[i] = -1;  
        
        int row = 0;
        for (int col = 0; col < n && row < m; ++col) {
            if (fabs(Ab[row][col]) > 1e-8) {
                index[col] = row;
                row++;
            }
        } 
        
        int anTuDo[MAX], dem = 0;
        for (int i = 0; i < n; ++i) {
            if (index[i] == -1) {
                anTuDo[dem++] = i;
            }
        }

        cout << "\nDang nghiem tong quat (p = 1):\n";
        fout << "\nDang nghiem tong quat (p = 1):\n";
        for (int i = 0; i < n; ++i) {
            if (index[i] == -1) {
                cout << "x" << i + 1 << " = t" << i + 1 << endl;
                fout << "x" << i + 1 << " = t" << i + 1 << endl;
            } else {
                int r = index[i];
                cout << "x" << i + 1 << " = ";
                fout << "x" << i + 1 << " = ";
                insothuc(Ab[r][n], pre,fout);
                for (int j = 0; j < dem; ++j) {
                    int c = anTuDo[j];
                    double heso = -Ab[r][c];
                    if (fabs(heso) > 1e-8) {
                        cout << " + (";
                        fout << " + (";
                        insothuc(heso, pre,fout);
                        cout << ") * t" << c + 1;
                        fout << ") * t" << c + 1;
                    }
                }
                cout << endl;
                fout << endl;
            }
        }
    }
}

void gaussjordan(int m, int n, int p, double A[MAX][MAX], double b[MAX][MAX], int pre,ofstream &fout) {
    double pivot, temp; 
    int i, j;
    int pivotRow;
    double Ab[MAX][2*MAX];
    int kq = ketLuanNghiem(m, n, p, A, b, pre,fout);
    matranbosung(m, n, p, A, b, Ab); 
    
    for (i = 0; i < m; i++) {
        pivotRow = -1;
        for (j = i; j < m; j++) {
            if (fabs(Ab[j][i] - 1.0) < 1e-8 || fabs(Ab[j][i] + 1.0) < 1e-8) {
                pivotRow = j;
                break; 
            }
        }
        if (pivotRow == -1) {
            pivotRow = i;
            for (int j = i + 1; j < m; j++) {
                if (fabs(Ab[j][i]) > fabs(Ab[pivotRow][i])) {
                    pivotRow = j;
                }
            }
        } 
        if (fabs(Ab[pivotRow][i]) < 1e-8) {
            continue;
        }    
        if (pivotRow != i) {
            for (int k = 0; k < n + p; k++) {
                swap(Ab[i][k], Ab[pivotRow][k]); 
            } 
        }	   
        pivot = Ab[i][i];
        for (j = 0; j < n + p; j++) {
            Ab[i][j] /= pivot; 
        }
        for (j = 0; j < m; j++) {
            temp = Ab[j][i];
            if (j != i) {
                for (int k = 0; k < n + p; k++) {
                    Ab[j][k] -= Ab[i][k] * temp;
                }
            }
        }
       cout << "Buoc " << i + 1 << ":\n";
        fout << "Buoc " << i + 1 << ":\n";
        inmatran(m, n + p, Ab, pre, fout);
        cout << endl; 
        fout << endl; 
    }  
    
    if (kq == 0) {
        cout << "He phuong trinh vo nghiem." << endl;
        fout << "He phuong trinh vo nghiem." << endl;
    } else if (kq == 1) {
        cout << "He phuong trinh co nghiem duy nhat." << endl;
        fout << "He phuong trinh co nghiem duy nhat." << endl;
        for (i = 0; i < n ; i++) {
            cout << "x" << i + 1 << " = ";
            fout << "x" << i + 1 << " = ";
            insothuc(Ab[i][n], pre, fout); 
            cout << endl;
            fout << endl;
        }
    } else if (kq == 2) {
        cout << "He phuong trinh co vo so nghiem." << endl;	
        fout << "He phuong trinh co vo so nghiem." << endl;	
        int index[MAX]; 
        for (int i = 0; i < n; ++i) index[i] = -1;  
        
        int row = 0;
        for (int col = 0; col < n && row < m; ++col) {
            if (fabs(Ab[row][col]) > 1e-8) {
                index[col] = row;
                row++;
            }
        } 
        
        int anTuDo[MAX], dem = 0;
        for (int i = 0; i < n; ++i) {
            if (index[i] == -1) {
                anTuDo[dem++] = i;
            }
        }
        
        cout << "\nDang nghiem tong quat:\n";
        fout << "\nDang nghiem tong quat:\n";
        
        for (int i = 0; i < n; ++i) {
            if (index[i] == -1) {
                cout << "x" << i + 1 << " = t" << i + 1 << endl;
                fout << "x" << i + 1 << " = t" << i + 1 << endl;
            } else {
                int r = index[i];
                cout << "x" << i + 1 << " = ";
                fout << "x" << i + 1 << " = ";
                insothuc(Ab[r][n], pre, fout);
                for (int j = 0; j < dem; ++j) {
                    int c = anTuDo[j];
                    double heso = -Ab[r][c];
                    if (fabs(heso) > 1e-8) {
                        cout << " + ("; fout << " + (";
                        insothuc(heso, pre, fout);
                        cout << ") * t" << c + 1;
                        fout << ") * t" << c + 1;
                    }
                }
                cout << endl;
                fout << endl;
            }
        }
    }
}
void docMatranTuFile(int &m, int &n, double A[MAX][MAX]) {
    ifstream fin("input1.txt");
    if (!fin.is_open()) {
        cout << "Khong the mo file input1.txt\n";
        return;
    }
    if (!(fin >> m >> n)) {
        cout << "Loi: Khong doc duoc kich thuoc ma tran (m, n)!\n";
        fin.close();
        return;
    }
    if (m <= 0 || n <= 0 || m > MAX || n > MAX) {
        cout << "Loi: Kich thuoc ma tran khong hop le! (m=" << m << ", n=" << n << ")\n";
        fin.close();
        return;
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(fin >> A[i][j])) {
                cout << "Loi: Du lieu ma tran tai dong " << i+1 << ", cot " << j+1 << " khong hop le hoac thieu du lieu!\n";
                fin.close();
                return;
            }
        }
    }
    fin.close();
    cout << "Da doc ma tran " << m << "x" << n << " tu file input1.txt\n";
}

void docHeTuFile(int &m, int &n, int &p, double A[MAX][MAX], double b[MAX][MAX]) {
    ifstream fin("input1.txt");
    if (!fin.is_open()) {
        cout << "Loi: Khong the mo file input.txt\n";
        return;
    }
    if (!(fin >> m >> n >> p)) {
        cout << "Loi: Khong the doc m, n, p tu file (thieu hoac sai dinh dang)\n";
        fin.close();
        return;
    }
    if (m <= 0 || n <= 0 || p <= 0 || m > MAX || n > MAX || p > MAX) {
        cout << "Loi: Kich thuoc khong hop le. m=" << m << ", n=" << n << ", p=" << p << "\n";
        fin.close();
        return;
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(fin >> A[i][j])) {
                cout << "Loi: Du lieu khong hop le hoac thieu tai A[" << i + 1 << "][" << j + 1 << "]\n";
                fin.close();
                return;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            if (!(fin >> b[i][j])) {
                cout << "Loi: Du lieu khong hop le hoac thieu tai b[" << i + 1 << "][" << j + 1 << "]\n";
                fin.close();
                return;
            }
        }
    }
    cout << "Da doc ma tran A (" << m << "x" << n << ") va b (" << m << "x" << p << ") tu file input.txt\n";
    fin.close();
}

int menuDong(const char *options[], int size) {
    int chon = 0;
    int key;
    while (true) {
        system("cls");
        cout << "=========== MENU ===========\n\n";
        for (int i = 0; i < size; ++i) {
            if (i == chon) {
                cout << ">> " << options[i] << " <<\n";
            } else {
                cout << "   " << options[i] << "\n";
            }
        }
        cout << "\nSu dung phim mui ten de chon. Enter de xac nhan." << endl;

        key = getch();
        if (key == 224) {
            key = getch();
            if (key == 72) chon = (chon - 1 + size) % size;
            else if (key == 80) chon = (chon + 1) % size;
        } else if (key == 13) {
            return chon;
        }
    }
}

