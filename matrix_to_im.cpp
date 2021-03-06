#ifndef MATRIX_TO_IM_CPP
#define MATRIX_TO_IM_CPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <array>

using namespace std;

/*BGRA for some reason*/
int matrix_to_im(int xsize, int ysize, unsigned char*** imin){

	/*file*/
	const char* imout = "./img/im.bmp";
	int tsize;/*bitmap size 4*pixels*/
	int fsize;/*file size*/
	unsigned char* xsizec = new unsigned char[4];
	unsigned char* ysizec = new unsigned char[4];
	unsigned char* tsizec = new unsigned char[4];
	unsigned char* fsizec = new unsigned char[4];

	tsize = ysize*xsize*4;
	fsize = 124+tsize;

	/*final file*/
	unsigned char* bytes = new unsigned char[fsize];


	xsizec[3] = (unsigned char)(xsize/(256*256*256));
	xsizec[2] = (unsigned char)((xsize%(256*256*256))/(256*256));
	xsizec[1] = (unsigned char)((xsize%(256*256))/256);
	xsizec[0] = (unsigned char)(xsize%256);

	ysizec[3] = (unsigned char)(ysize/(256*256*256));
	ysizec[2] = (unsigned char)((ysize%(256*256*256))/(256*256));
	ysizec[1] = (unsigned char)((ysize%(256*256))/256);
	ysizec[0] = (unsigned char)(ysize%256);

	tsizec[3] = (unsigned char)(tsize/(256*256*256));
	tsizec[2] = (unsigned char)((tsize%(256*256*256))/(256*256));
	tsizec[1] = (unsigned char)((tsize%(256*256))/256);
	tsizec[0] = (unsigned char)(tsize%256);

	fsizec[3] = (unsigned char)(fsize/(256*256*256));
	fsizec[2] = (unsigned char)((fsize%(256*256*256))/(256*256));
	fsizec[1] = (unsigned char)((fsize%(256*256))/256);
	fsizec[0] = (unsigned char)(fsize%256);


	/*BMP header*/	
	bytes[0] = 0x42;
	bytes[1] = 0x4D;

	//////*file size*///////
	bytes[2] = fsizec[0];
	bytes[3] = fsizec[1];
	bytes[4] = fsizec[2];
	bytes[5] = fsizec[3];

	/*header stuff*/
	bytes[6] = 0x00;
	bytes[7] = 0x00;
	bytes[8] = 0x00;
	bytes[9] = 0x00;

	/*offset to pixels*/
	bytes[10] = 0x7A;
	bytes[11] = 0x00;
	bytes[12] = 0x00;
	bytes[13] = 0x00;


	/*DIB header*/
	/*bytes in header*/
	bytes[14] = 0x6c;
	bytes[15] = 0x00;
	bytes[16] = 0x00;
	bytes[17] = 0x00;
	
	/////*width of bitmap*/////
	bytes[18] = xsizec[0];
	bytes[19] = xsizec[1];
	bytes[20] = xsizec[2];
	bytes[21] = xsizec[3];

	/////*height of bitmap*/////
	bytes[22] = ysizec[0];
	bytes[23] = ysizec[1];
	bytes[24] = ysizec[2];
	bytes[25] = ysizec[3];

	/*color planes*/
	bytes[26] = 0x01;
	bytes[27] = 0x00;

	/////*bits per pixel*/////
	bytes[28] = 0x20;
	bytes[29] = 0x00;

	/*bitfield*/
	bytes[30] = 0x03;
	bytes[31] = 0x00;
	bytes[32] = 0x00;
	bytes[33] = 0x00;

	/////*size of raw data 4*pixels */////
	bytes[34] = tsizec[0];
	bytes[35] = tsizec[1];
	bytes[36] = tsizec[2];
	bytes[37] = tsizec[3];

	/*other header stuff*/
	bytes[38] = 0x13;
	bytes[39] = 0x0B;
	bytes[40] = 0x00;
	bytes[41] = 0x00;

	bytes[42] = 0x13;
	bytes[43] = 0x0B;
	bytes[44] = 0x00;
	bytes[45] = 0x00;

	bytes[46] = 0x00;
	bytes[47] = 0x00;
	bytes[48] = 0x00;
	bytes[49] = 0x00;

	bytes[50] = 0x00;
	bytes[51] = 0x00;
	bytes[52] = 0x00;
	bytes[53] = 0x00;

	bytes[54] = 0x00;
	bytes[55] = 0x00;
	bytes[56] = 0xFF;
	bytes[57] = 0x00;

	bytes[58] = 0x00;
	bytes[59] = 0xFF;
	bytes[60] = 0x00;
	bytes[61] = 0x00;

	bytes[62] = 0xFF;
	bytes[63] = 0x00;
	bytes[64] = 0x00;
	bytes[65] = 0x00;

	bytes[66] = 0x00;
	bytes[67] = 0x00;
	bytes[68] = 0x00;
	bytes[69] = 0xFF;

	bytes[70] = 0x20;
	bytes[71] = 0x6E;
	bytes[72] = 0x69; 
	bytes[73] = 0x57;

	for (int i=74; i<110;i++){
		bytes[i] = 0x00;
	}

	bytes[110] = 0x00;
	bytes[111] = 0x00;
	bytes[112] = 0x00;
	bytes[113] = 0x00;

	bytes[114] = 0x00;
	bytes[115] = 0x00;
	bytes[116] = 0x00;
	bytes[117] = 0x00;

	bytes[118] = 0x00;
	bytes[119] = 0x00;
	bytes[120] = 0x00;
	bytes[121] = 0x00;


	/*BGRA for some reason*/
	/////*start of array bitmap*/////
	for(int i=0;i<ysize;i++){
		for(int j=0;j<xsize;j++){
			for(int k=0;k<4;k++){
				bytes[(122+i*xsize*4+j*4+k)] = imin[i][j][k];
			}
		}
	}



/*ending bit*/
	bytes[fsize-2] = 0x00;
	bytes[fsize-1] = 0x00;


	
	/*output*/
	ofstream myfile(imout);

	for(int i=0;i<fsize;i++){
		myfile << bytes[i];
	}
	myfile.close();

	
	/*deallocate*/
	delete(bytes);

	return 0;
	

}

#endif
