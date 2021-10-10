#include <iostream>
#include "mylib.h"
#include <vector>
using namespace std;

#define consoleWidth 119
#define consoleHight 29

struct Coordinates {
	int x, y;
};

void rowBox(int x, int y, int width, int& boxColor) {
	//HÀM VẼ TRỤC NGANG CỦA BOX
	//x, y là tọa độ bắt đầu của trục (vẽ từ trái qua phải) 	//width là kích thước trục ngang
	textcolor(boxColor);
	gotoXY(x + 1, y);
	for (int ix = 0; ix != width; ix++)
		cout << char(196);
}

void colBox(int x, int y, int width, int hight, int& boxColor) {
	//HÀM VẼ TRỤC ĐỨNG CỦA BOX
	//x, y là tọa độ bắt đầu của trục (vẽ từ trên xuống)	//hight là kích thước trục đứng	
	textcolor(boxColor);
	for (int iy = 0; iy != hight; iy++) {		
		gotoXY(x, y + iy);		//vẽ đường bên trái box
		cout << char(179);
		gotoXY(x + width, y + iy);
		cout << char(179);		//vẽ đường bên phải box
	}
}

void cornerBox(int x, int y, int width, int hight, int& boxColor){
	//HÀM VẼ CÁC GÓC CỦA BOX Ở GIỮA (TRỪ CÁC GÓC CỦA TABLE)
	textcolor(boxColor);
	gotoXY(x, y + hight);			//góc bên phải
	cout << char(195);
	gotoXY(x + width, y + hight);	//góc bên trái
	cout << char(180);
}

void backroundBox(int x, int y, int width, int hight, int& charColor) {
	//HÀM TẠO BACKROUND cho box
	textcolor(charColor);
	for (int iy = 0; iy != hight; iy++) {
		gotoXY(x, y + iy);
		for (int ix = 0; ix != width; ix++)
			cout << " ";
	}
}

void dataBox(int x, int y, int width, int hight, string s, int& charColor) {
	//HÀM VẼ NỀN VÀ XUẤT TÊN CỦA OPTION 
	backroundBox(x + 1, y + 1, width - 1, hight - 1, charColor);	//vẽ nền

	textcolor(charColor);
	gotoXY(x + (width - s.length()) / 2, y + hight / 2);		//đến vị trí sao cho sau khi vẽ chuỗi có thể nằm ở giữa
	cout << s;	
}

void box(int x, int y, int width, int hight, string s, int& boxColor, int& charColor) {
	//HÀM VẼ 1 BOX
	//x, y là tọa độ góc trái trên box muốn tạo 	//width, hight là chiều rộng và chiều cao của box
	rowBox(x, y, width - 1, boxColor);					//vẽ đường trên của box
	colBox(x, y + 1, width, hight - 1, boxColor);		//vẽ cột
	cornerBox(x, y, width, hight, boxColor);			//vẽ các góc của box
	dataBox(x, y, width, hight, s, charColor);			//tạo tên và màu nền cho box
}

void cornerTable(int x, int y, int width, int hight, int n, int& boxColor) {
	//HÀM VẼ 4 GÓC CỦA TABLE
	textcolor(boxColor);
	gotoXY(x, y);				//vẽ góc trái trên
	cout << char(218);
	gotoXY(x + width, y);		//vẽ góc phải trên
	cout << char(191);

	y += hight * n;				//thay đổi giá trị để di chuyển xuống dòng cuối
	gotoXY(x, y);				//vẽ góc trái dưới
	cout << char(192);
	gotoXY(x + width, y);		//vẽ góc phải dưới
	cout << char(217);

}

void table(int x, int y, int width, int hight, vector<string> infor, int& tableColor, int& charColor) {
	//HÀM TẠO TABLE
	int tempY = y;
	for (auto e:infor) {
		box(x, y, width, hight, e, tableColor, charColor);	//vẽ box
		y += hight;
	}
	rowBox(x, y, width - 1, tableColor);		//vẽ dòng dưới cùng của table
	y = tempY;	
	cornerTable(x, y, width, hight, infor.size(), tableColor);	//vẽ 4 góc của table
	
}

vector<string> tableInformation() {		//HÀM LẤY THÔNG TIN CỦA TỪNG BOX TRONG TABLE
	vector<string>	infor;
	infor.push_back("option 1");
	infor.push_back("option 2");
	infor.push_back("option 3");
	infor.push_back("option 4");
	infor.push_back("option 5");
	return infor;
}

void displayTable(int width ,int hight) {	
	//HÀM XUẤT OPNTION TABLE (input kích thước của bảng)
	vector<string> infor = tableInformation();	
	//căn giữa màn hình console kích thước 119 * 19
	int bewConsoleWidth = (consoleWidth - width) / 2, bewConsoleHight = (consoleHight - hight * infor.size()) / 2;
	int tableColor = 123, charColor = 224;		//boxcolor là màu viền của table, charcolor là màu chữ và màu nền của table

	
	table(bewConsoleWidth, bewConsoleHight, width, hight, infor, tableColor, charColor);	//hàm tạo bảng

	//tạo màu cho ô được chọn
	int optionColor = 64, optionX = bewConsoleWidth, optionY = bewConsoleHight, i = 0;		//màu và vị trí của option
	dataBox(optionX, optionY, width, hight, infor[i], optionColor);		//hàm tạo màu khác cho option

	while (true) {		//sử dụng 2 phím (lên, xuống) để điều kiển
		if (_kbhit()) {		//hàm phát hiện có kí tự nhập vào
			char c = _getch();
			if (c == 13)		//khi nhập enter sẽ kết thúc while
				break;
			else
				if (c == -32) {
					c = _getch();
					if (c == 80 && i < infor.size() - 1) {	//đi xuống
						dataBox(optionX, optionY, width, hight, infor[i], charColor);			//vẽ chồng màu lên option
						optionY += hight;
						i++;
						dataBox(optionX, optionY, width, hight, infor[i], optionColor);			//vẽ lại option mới
					}
					else
						if (c == 72 && i > 0) {	//đi lên
							dataBox(optionX, optionY, width, hight, infor[i], charColor);		//vẽ chồng màu lên option
							optionY -= hight;
							i--;
							dataBox(optionX, optionY, width, hight, infor[i], optionColor);		//vẽ lại option mới
						}
				}
		}
	}	
}


int main()
{
	ShowCur(0);		//hàm tắt con trỏ
	//cout << _getch() << _getch();
	displayTable(30, 2);
	cout << endl;
	gotoXY(consoleWidth, consoleHight);
}