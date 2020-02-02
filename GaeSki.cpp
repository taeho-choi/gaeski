#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm.hpp"
#include "GL/ext.hpp"
#include "GL/gtc/matrix_transform.hpp"
#include "GL/freeglut_ext.h"

#define PI 3.1415926535f

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
int gwidth = 1250;
int gheight = 630;

bool pendingTimerStop = false;

float startAniRotValue = 90.f;
float startAniTransValue = -15.f;

bool startAni = false;
bool isStartPage = true;
bool isStart = false;
bool isEnd = false;
bool isOver = false;

bool moveLeft = false;
bool moveRight = false;

GLuint programID;

GLuint VAO[10];
GLuint VBO[10];
GLuint Textures[100];

glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 transMatrix = glm::mat4(1.0f);
glm::mat4 rotMatrix = glm::mat4(1.0f);
glm::mat4 myMatrix = glm::mat4(1.0f);
glm::mat4 defaultMatrix = glm::mat4(1.0f);

glm::mat4 scoreMatrix = glm::mat4(1.0f);
glm::mat4 score1Matrix = glm::mat4(1.0f);
glm::mat4 score10Matrix = glm::mat4(1.0f);
glm::mat4 score100Matrix = glm::mat4(1.0f);

glm::mat4 lastMatrix = glm::mat4(1.0f);
glm::mat4 startAniMatrix = glm::mat4(1.0f);

glm::mat4 sideMatrix = glm::mat4(1.0f);
glm::mat4 verticalMatrix = glm::mat4(1.0f);

int score = 0;
float rotValue = 0.f;
float nowRot = 0.f;
float sideValue = 0.f;
float nowSide = 0.f;
float verticalValue = 0.f;
float fowardValue = 0.f;
float nowVertical = 0.f;

bool eatenCoin[300];
bool eatenSnail[300];
bool eatenMagnet[300];
bool eatenGhost[300];

float coinSide[300];
float treeSide[300];
float magnetSide[300];
float snailSide[300];
float ghostSide[300];

bool isSnail = false;
int snailCnt = 100;

bool isMagnet = false;
int magnetCnt = 500;

bool isGhost = false;
int ghostCnt = 500;

float fenceData1[2400];
float fenceData2[2400];

glm::mat4 gaeMatrix = glm::mat4(1.0f);
glm::mat4 gaeVertMat = glm::mat4(1.0f);
glm::mat4 gaeVertBehindMat = glm::mat4(1.0f);
glm::mat4 gaeVertFrontMat = glm::mat4(1.0f);
glm::mat4 gaeHoriMat = glm::mat4(1.0f);
glm::mat4 gaeHoriLeftMat = glm::mat4(1.0f);
glm::mat4 gaeHoriRightMat = glm::mat4(1.0f);
glm::mat4 skiMat = glm::mat4(1.0f);
glm::mat4 skiRightMat = glm::mat4(1.0f);
glm::mat4 skiLeftMat = glm::mat4(1.0f);

glm::mat4 logoMat = glm::mat4(1.0f);

glm::mat4 coinMatrix = glm::mat4(1.0f);
glm::mat4 snailMatrix = glm::mat4(1.0f);
glm::mat4 magnetMatrix = glm::mat4(1.0f);
glm::mat4 ghostMatrix = glm::mat4(1.0f);


glm::mat4 treeMatrix = glm::mat4(1.0f);
glm::mat4 treeTransMatrix = glm::mat4(1.0f);
glm::mat4 treeSideMatrix = glm::mat4(1.0f);

glm::mat4 coinTransMatrix = glm::mat4(1.0f);
glm::mat4 snailTransMatrix = glm::mat4(1.0f);
glm::mat4 magnetTransMatrix = glm::mat4(1.0f);
glm::mat4 ghostTransMatrix = glm::mat4(1.0f);

glm::mat4 snailSideMatrix = glm::mat4(1.0f);
glm::mat4 magnetSideMatrix = glm::mat4(1.0f);
glm::mat4 ghostSideMatrix = glm::mat4(1.0f);

glm::mat4 gaeRotMatrix = glm::mat4(1.0f);

glm::mat4 linesMatrix = glm::mat4(1.0f);

float vertexData[] = {
	//앞
	-0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
	-0.2, 0.2, 0.2, 0.0, 0.0, 1.0,
	0.2, 0.2, 0.2, 0.0, 0.0, 1.0,

	0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
	-0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
	0.2, 0.2, 0.2, 0.0, 0.0, 1.0,
	//왼
	-0.2, 0.2, -0.2, -1.0, 0.0, 0.0,
	-0.2, 0.2, 0.2, -1.0, 0.0, 0.0,
	-0.2, -0.2, 0.2, -1.0, 0.0, 0.0,

	-0.2, 0.2, -0.2, -1.0, 0.0, 0.0,
	-0.2, -0.2, 0.2, -1.0, 0.0, 0.0,
	-0.2, -0.2, -0.2, -1.0, 0.0, 0.0,
	//오른
	0.2, -0.2, 0.2, 1.0, 0.0, 0.0,
	0.2, 0.2, 0.2, 1.0, 0.0, 0.0,
	0.2, 0.2, -0.2, 1.0, 0.0, 0.0,

	0.2, -0.2, 0.2, 1.0, 0.0, 0.0,
	0.2, 0.2, -0.2, 1.0, 0.0, 0.0,
	0.2, -0.2, -0.2, 1.0, 0.0, 0.0,
	//위
	-0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
	-0.2, 0.2, -0.2, 0.0, 1.0, 0.0,
	0.2, 0.2, -0.2, 0.0, 1.0, 0.0,

	0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
	-0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
	0.2, 0.2, -0.2, 0.0, 1.0, 0.0,
	//뒤
	0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
	-0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
	-0.2, -0.2, -0.2, 0.0, 0.0, -1.0,

	0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
	-0.2, -0.2, -0.2, 0.0, 0.0, -1.0,
	0.2, -0.2, -0.2, 0.0, 0.0, -1.0,
	//밑
	0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
	-0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
	-0.2, -0.2, 0.2, 0.0, -1.0, 0.0,

	0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
	-0.2, -0.2, 0.2, 0.0, -1.0, 0.0,
	0.2, -0.2, 0.2, 0.0, -1.0, 0.0,
};

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	// 쉐이더들 생성
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// 버텍스 쉐이더 코드를 파일에서 읽기
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path, ios::in);
	if (VertexShaderStream.is_open())
	{
		stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		printf("파일 %s 를 읽을 수 없음\n", vertex_file_path);
		return 0;
	}

	// 프래그먼트 쉐이더 코드를 파일에서 읽기
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, ios::in);
	if (FragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else
	{
		printf("파일 %s 를 읽을 수 없음\n", fragment_file_path);
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// 버텍스 쉐이더를 컴파일
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// 프래그먼트 쉐이더를 컴파일
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// 프로그램에 링크
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// 프로그램 검사
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void drawFence()
{
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(fenceData1), fenceData1, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix));
	glBindVertexArray(VAO[0]);
	glBindTexture(GL_TEXTURE_2D, Textures[25]);
	glDrawArrays(GL_LINES, 0, 400);

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(fenceData2), fenceData2, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix));
	glBindVertexArray(VAO[0]);
	glBindTexture(GL_TEXTURE_2D, Textures[25]);
	glDrawArrays(GL_LINES, 0, 400);
}

void InitTexture()
{
	int widthImage[100], heightImage[100], numberOfChannel[100];

	glGenTextures(100, Textures);

	glBindTexture(GL_TEXTURE_2D, Textures[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load("snow.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_set_flip_vertically_on_load(1);

	//

	glBindTexture(GL_TEXTURE_2D, Textures[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data2 = stbi_load("dog_top.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);

	//

	glBindTexture(GL_TEXTURE_2D, Textures[2]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data3 = stbi_load("dog_behind.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data3);


	/////

	glBindTexture(GL_TEXTURE_2D, Textures[3]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data4 = stbi_load("dog_side.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data4);

	/////

	glBindTexture(GL_TEXTURE_2D, Textures[4]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data5 = stbi_load("ski.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data5);

	/////

	glBindTexture(GL_TEXTURE_2D, Textures[5]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data6 = stbi_load("start.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data6);

	/////

	glBindTexture(GL_TEXTURE_2D, Textures[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data7 = stbi_load("logo.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data7);

	//숫자 텍스쳐
	glBindTexture(GL_TEXTURE_2D, Textures[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data8 = stbi_load("score.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data8);

	glBindTexture(GL_TEXTURE_2D, Textures[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data9 = stbi_load("0.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data9);

	glBindTexture(GL_TEXTURE_2D, Textures[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data10 = stbi_load("1.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data10);

	glBindTexture(GL_TEXTURE_2D, Textures[10]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data11 = stbi_load("2.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data11);

	glBindTexture(GL_TEXTURE_2D, Textures[11]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data12 = stbi_load("3.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data12);

	glBindTexture(GL_TEXTURE_2D, Textures[12]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data13 = stbi_load("4.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data13);

	glBindTexture(GL_TEXTURE_2D, Textures[13]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data14 = stbi_load("5.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data14);

	glBindTexture(GL_TEXTURE_2D, Textures[14]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data15 = stbi_load("6.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data15);

	glBindTexture(GL_TEXTURE_2D, Textures[15]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data16 = stbi_load("7.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data16);

	glBindTexture(GL_TEXTURE_2D, Textures[16]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data17 = stbi_load("8.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data17);

	glBindTexture(GL_TEXTURE_2D, Textures[17]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data18 = stbi_load("9.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data18);

	//코인
	glBindTexture(GL_TEXTURE_2D, Textures[18]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data19 = stbi_load("coin.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data19);

	glBindTexture(GL_TEXTURE_2D, Textures[19]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data20 = stbi_load("shadow.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data20);

	//자석
	glBindTexture(GL_TEXTURE_2D, Textures[20]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data21 = stbi_load("magnet.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data21);

	//달팽이
	glBindTexture(GL_TEXTURE_2D, Textures[21]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data22 = stbi_load("snail.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data22);

	//나무
	glBindTexture(GL_TEXTURE_2D, Textures[22]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data23 = stbi_load("tree.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data23);

	//클리어
	glBindTexture(GL_TEXTURE_2D, Textures[23]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data24 = stbi_load("clear.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data24);

	//나무
	glBindTexture(GL_TEXTURE_2D, Textures[24]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data25 = stbi_load("ghost.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data25);

	//펜스
	glBindTexture(GL_TEXTURE_2D, Textures[25]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data26 = stbi_load("fence.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data26);

	//게임오버
	glBindTexture(GL_TEXTURE_2D, Textures[26]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data27 = stbi_load("over.png", &widthImage[0], &heightImage[0], &numberOfChannel[0], 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage[0], heightImage[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, data27);
}

void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy)
{
	int w = gwidth;
	int h = gheight;
	*ox = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
	*oy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}

void Mouse(int button, int state, int x, int y)
{
	float ox;
	float oy;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		convertDeviceXY2OpenglXY(x, y, &ox, &oy);
		//cout << ox << " " << oy << endl;
		if (isStartPage && fabs(ox) < 0.55f && oy > -0.3f && oy < 0.1f)
		{
			startAni = true;
			isStartPage = false;
		}
	}
}

void Timer(int n)
{
	// 시작 버튼을 누르면 카메라 애니메이션이 시작한다.
	if (startAni)
	{
		if (startAniRotValue > 0.f || startAniTransValue < 0.f)
		{

			startAniRotValue -= 0.6f;
			startAniTransValue += 0.1f;
		}
		else
		{
			startAni = false;
			isStart = true;
		}
	}

	// 처음 카메라 애니메이션이 끝난 후
	if (isStart)
	{
		// 자석 아이템 먹었을 때
		if (isMagnet)
		{
			int intNowVertical = (int)nowVertical + 1;

			for (int i = intNowVertical - 1; i < intNowVertical + 1; i++)
			{
				if (coinSide[i] > -nowSide)
				{
					coinSide[i] -= (coinSide[i] + nowSide) / 1.5f;
				}
				if (coinSide[i] < -nowSide)
				{
					coinSide[i] += (-nowSide - coinSide[i]) / 1.5f;
				}
			}
			magnetCnt--;
			if (magnetCnt == 0)
			{
				isMagnet = false;
				magnetCnt = 500;
			}
		}

		//게임 클리어 시 멈추기
		if (nowVertical > 300.f)
		{
			if (fowardValue > 0.f)
			{
				fowardValue -= 0.00075f;
				sideValue = 0.f;
			}
			else
			{
				fowardValue = 0.f;
				isEnd = true;
			}
		}
		// 달팽이 아이템 먹었을 때
		else if (isSnail)
		{
			fowardValue = 0.01f;
			snailCnt--;
			if (snailCnt == 0)
			{
				isSnail = false;
				snailCnt = 100;
			}
		}
		// 앞으로 이동을 가속도로 설정한다.
		else if (fowardValue < 0.1f && !isOver)
		{
			fowardValue += 0.001f;
		}

		// 고스트 아이템 먹었을 때
		if (isGhost)
		{
			ghostCnt--;
			if (ghostCnt == 0)
			{
				isGhost = false;
				ghostCnt = 500;
			}
		}

		// 좌우 이동 버튼 입력에 따라 가속도로 설정하고 관성이 적용되게 한다.
		if (moveLeft && !isEnd && !isOver)
		{
			if (sideValue < 0.05f)
			{
				sideValue += 0.0015f;
			}
			if (rotValue < 1.0f)
			{
				rotValue += 0.6f;
			}
		}
		else if (moveRight && !isEnd && !isOver)
		{
			if (sideValue > -0.05f)
			{
				sideValue -= 0.0015f;
			}
			if (rotValue > -1.0f)
			{
				rotValue -= 0.6f;
			}
		}
	}

	glutPostRedisplay(); // 화면 재출력
	if (!pendingTimerStop)
	{
		pendingTimerStop = true;
		glutTimerFunc(20, Timer, 1); // 타이머함수 재 설정
	}
	pendingTimerStop = false;
}

void Init()
{
	glEnable(GL_DEPTH_TEST);

	programID = LoadShaders("vs.glsl", "fs.glsl"); // shader 파일과 fragment 파일을 프로그램 링크

	defaultMatrix = glm::translate(defaultMatrix, glm::vec3(0.f, -0.045f, 0.9f));

	//스코어 매트릭스 초기 세팅
	scoreMatrix = glm::translate(scoreMatrix, glm::vec3(-1.0f, 0.7f, 0.f));
	score1Matrix = glm::translate(score1Matrix, glm::vec3(-0.55f, 0.7f, 0.f));
	score10Matrix = glm::translate(score10Matrix, glm::vec3(-0.65f, 0.7f, 0.f));
	score100Matrix = glm::translate(score100Matrix, glm::vec3(-0.75f, 0.7f, 0.f));

	//로고 매트릭스 초기 세팅
	logoMat = glm::translate(logoMat, glm::vec3(0.f, 0.3f, 0.f));

	// 카메라 매트릭스 초기 세팅
	startAniMatrix = glm::mat4(1.0f);
	startAniMatrix = glm::rotate(startAniMatrix, glm::radians(startAniRotValue), glm::vec3(1.0f, 0.0f, 0.0f));
	startAniMatrix = glm::translate(startAniMatrix, glm::vec3(0.f, startAniTransValue, 0.f));

	lastMatrix = glm::translate(lastMatrix, glm::vec3(0.f, -0.8f, 0.f));

	// 개 매트릭스 초기 세팅
	gaeMatrix = glm::scale(gaeMatrix, glm::vec3(0.3f, 0.4f, 0.3f));
	gaeMatrix = glm::translate(gaeMatrix, glm::vec3(0.f, 0.2f, 0.f));

	gaeVertMat = glm::scale(gaeVertMat, glm::vec3(0.3f, 0.25f, 0.3f));
	gaeVertMat = glm::rotate(gaeVertMat, glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
	gaeVertBehindMat = glm::translate(gaeVertBehindMat, glm::vec3(0.f, 0.14f, -0.06f));
	gaeVertFrontMat = glm::translate(gaeVertFrontMat, glm::vec3(0.f, 0.14f, -0.19f));

	gaeHoriMat = glm::scale(gaeVertMat, glm::vec3(0.3f, 0.25f, 0.3f));
	gaeHoriMat = glm::rotate(gaeVertMat, glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
	gaeHoriMat = glm::rotate(gaeVertMat, glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
	gaeHoriRightMat = glm::translate(gaeHoriRightMat, glm::vec3(0.1824f, 0.14f, 0.f));
	gaeHoriLeftMat = glm::translate(gaeHoriLeftMat, glm::vec3(0.0575f, 0.14f, 0.f));

	skiMat = glm::scale(skiMat, glm::vec3(0.2f, 0.2f, 0.5f));
	skiLeftMat = glm::translate(skiLeftMat, glm::vec3(-0.05f, -0.04f, 0.f));
	skiRightMat = glm::translate(skiRightMat, glm::vec3(0.05f, -0.04f, 0.f));

	// 코인 매트릭스 초기 세팅
	coinMatrix = glm::scale(coinMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
	coinMatrix = glm::translate(coinMatrix, glm::vec3(0.f, 1.0f, 0.f));

	coinMatrix = glm::rotate(coinMatrix, glm::radians(35.f), glm::vec3(1.0f, 0.0f, 0.0f));

	for (int i = 0; i < 300; i++)
	{
		eatenCoin[i] = false;
	}
	for (int i = 0; i < 300; i++)
	{
		coinSide[i] = -sin(PI / 180.0f * i * 5.f) * 5.f;
	}

	// 달팽이 매트릭스 초기 세팅
	snailMatrix = glm::scale(snailMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
	snailSideMatrix = glm::translate(snailSideMatrix, glm::vec3(0.f, 0.2f, 0.f));

	snailMatrix = glm::rotate(snailMatrix, glm::radians(35.f), glm::vec3(1.0f, 0.0f, 0.0f));

	for (int i = 0; i < 300; i++)
	{
		eatenSnail[i] = false;
	}
	for (int i = 0; i < 300; i++)
	{
		snailSide[i] = -sin(PI / 180.0f * i * 5.f) * 5.f;
	}

	// 자석 매트릭스 초기 세팅
	magnetMatrix = glm::scale(magnetMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
	magnetSideMatrix = glm::translate(magnetSideMatrix, glm::vec3(0.f, 0.2f, 0.f));

	magnetMatrix = glm::rotate(magnetMatrix, glm::radians(35.f), glm::vec3(1.0f, 0.0f, 0.0f));

	for (int i = 0; i < 300; i++)
	{
		eatenMagnet[i] = false;
	}
	for (int i = 0; i < 300; i++)
	{
		magnetSide[i] = (-sin(PI / 180.0f * i * 5.f) * 5.f) - 1.f;
	}

	// 고스트 매트릭스 초기 세팅
	ghostMatrix = glm::scale(ghostMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
	ghostSideMatrix = glm::translate(ghostSideMatrix, glm::vec3(0.f, 0.2f, 0.f));

	ghostMatrix = glm::rotate(ghostMatrix, glm::radians(35.f), glm::vec3(1.0f, 0.0f, 0.0f));

	for (int i = 0; i < 300; i++)
	{
		eatenGhost[i] = false;
	}
	for (int i = 0; i < 300; i++)
	{
		ghostSide[i] = (-sin(PI / 180.0f * i * 5.f) * 5.f) + 1.f;
	}

	// 나무 매트릭스 초기 세팅
	treeMatrix = glm::scale(treeMatrix, glm::vec3(0.5f, 2.0f, 0.5f));
	treeSideMatrix = glm::translate(treeMatrix, glm::vec3(0.f, 0.f, 0.f));

	treeMatrix = glm::rotate(treeMatrix, glm::radians(10.f), glm::vec3(1.0f, 0.0f, 0.0f));

	for (int i = 0; i < 300; i++)
	{
		treeSide[i] = -sin(PI / 180.0f * i * 5.f) * 5.f + 0.3f;
	}

	// 펜스 데이터
	for (int i = 2399; i >= 0; i--)
	{
		if (i % 6 == 3)
		{
			fenceData1[i] = 1.0f;
		}
		if (i % 6 == 4 || i % 6 == 5 || i % 6 == 1)
		{
			fenceData1[i] = 0.01f;
		}
		if (i % 6 == 2)
		{
			fenceData1[i] = -(((float)i - 2) / 6);
		}
		if (i % 6 == 0)
		{
			fenceData1[i] = sin(PI / 180.0f * fenceData1[i + 2] * 5) * 5 - 3.f;
		}
	}

	for (int i = 2399; i >= 0; i--)
	{
		if (i % 6 == 3)
		{
			fenceData2[i] = 1.0f;
		}
		if (i % 6 == 4 || i % 6 == 5 || i % 6 == 1)
		{
			fenceData2[i] = 0.01f;
		}
		if (i % 6 == 2)
		{
			fenceData2[i] = -(((float)i - 2.f) / 6.f);
		}
		if (i % 6 == 0)
		{
			fenceData2[i] = sin(PI / 180.0f * fenceData2[i + 2] * 5) * 5 + 3.f;
		}
	}
	glutTimerFunc(10, Timer, 1);
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': // 초기화
		rotValue = 0.f;
		verticalValue = 0.f;
		Init();
		break;

	case 'a': // 왼쪽 이동 키
		moveLeft = true;
		break;

	case 'd': // 오른쪽 이동 키
		moveRight = true;
		break;

	case 'q': // 프로그램 종료
		exit(0);
		break;
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': // 왼쪽 이동 키 뗄 때
		moveLeft = false;
		break;

	case 'd': // 왼쪽 이동 키 뗄 때
		moveRight = false;
		break;
	}

	glutPostRedisplay();
}

void lines()
{
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	float floor[] = {
	20.f, 0.0f,400.0f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
	-20.0f, 0.0f, 400.0f,      0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
	-20.0f, 0.0f, -400.0f,      0.0f, 0.0f,      0.0f, 1.0f, 0.0f,

	20.0f,  0.0f,400.0f,      1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
	-20.0f,  0.0f,-400.0f,      0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
	20.0f,  0.0f, -400.0f,      1.0f, 0.0f,      0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(4, VBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor), floor, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[0]);
	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix));

	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 0.f, 1.f, 3.f);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
	glUniform3f(viewPosLocation, 0.0, 0.0, 1.0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawGae()
{
	float gae[] = {
		//위
		-0.2, 0.4, 0.2,      0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.2, 0.4, -0.2,   0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.2, 0.4, -0.2,      1.0f, 0.0f,      0.0f, 1.0f, 0.0f,

		0.2, 0.4, 0.2,      1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.2, 0.4, 0.2,      0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.2, 0.4, -0.2,      1.0f, 0.0f,      0.0f, 1.0f, 0.0f,

		//뒤
		-0.2, 0.4, 0.4,      0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.2, 0.4, -0.4,   0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.2, 0.4, -0.4,      1.0f, 0.0f,      0.0f, 1.0f, 0.0f,

		0.2, 0.4, 0.4,      1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.2, 0.4, 0.4,      0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.2, 0.4, -0.4,      1.0f, 0.0f,      0.0f, 1.0f, 0.0f,

		//스키
		-0.1, 0.4, 0.4,      0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.1, 0.4, -0.4,   0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.1, 0.4, -0.4,      1.0f, 0.0f,      0.0f, 1.0f, 0.0f,

		0.1, 0.4, 0.4,      1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.1, 0.4, 0.4,      0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.1, 0.4, -0.4,      1.0f, 0.0f,      0.0f, 1.0f, 0.0f,
	};
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	if (rotValue > 0.f && nowRot < 12.0f)
	{
		gaeRotMatrix = glm::rotate(gaeRotMatrix, glm::radians(rotValue), glm::vec3(0.0f, 1.0f, 0.0f));
		nowRot += rotValue;
	}
	else if (rotValue < 0.f && nowRot > -12.0f)
	{
		gaeRotMatrix = glm::rotate(gaeRotMatrix, glm::radians(rotValue), glm::vec3(0.0f, 1.0f, 0.0f));
		nowRot += rotValue;
	}

	glGenVertexArrays(2, VAO);
	glGenBuffers(4, VBO);

	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gae), gae, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//위
	glBindVertexArray(VAO[1]);
	glBindTexture(GL_TEXTURE_2D, Textures[1]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * lastMatrix * gaeRotMatrix * gaeMatrix));

	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 0.f, 0.5f, 0.5f);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
	glUniform3f(viewPosLocation, 0.0, 0.0, 1.0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//뒤
	glBindVertexArray(VAO[1]);
	glBindTexture(GL_TEXTURE_2D, Textures[2]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * lastMatrix * gaeRotMatrix * gaeVertBehindMat * gaeVertMat));

	glDrawArrays(GL_TRIANGLES, 6, 6);

	//앞
	glBindVertexArray(VAO[1]);
	glBindTexture(GL_TEXTURE_2D, Textures[2]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * lastMatrix * gaeRotMatrix * gaeVertFrontMat * gaeVertMat));

	glDrawArrays(GL_TRIANGLES, 6, 6);

	//왼
	glBindVertexArray(VAO[1]);
	glBindTexture(GL_TEXTURE_2D, Textures[3]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * lastMatrix * gaeRotMatrix * gaeHoriLeftMat * gaeHoriMat));

	glDrawArrays(GL_TRIANGLES, 6, 6);

	//오
	glBindVertexArray(VAO[1]);
	glBindTexture(GL_TEXTURE_2D, Textures[3]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * lastMatrix * gaeRotMatrix * gaeHoriRightMat * gaeHoriMat));

	glDrawArrays(GL_TRIANGLES, 6, 6);

	//스키
	glBindVertexArray(VAO[1]);
	glBindTexture(GL_TEXTURE_2D, Textures[4]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * lastMatrix * gaeRotMatrix * skiRightMat * skiMat));

	glDrawArrays(GL_TRIANGLES, 12, 6);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * lastMatrix * gaeRotMatrix * skiLeftMat * skiMat));

	glDrawArrays(GL_TRIANGLES, 12, 6);
}

void drawTree()
{
	float vertexData[] = {
		//앞
	 -0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
	 -0.2, 0.2, 0.2, 0.0, 0.0, 1.0,
	 0.2, 0.2, 0.2, 0.0, 0.0, 1.0,

	 0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
	 -0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
	 0.2, 0.2, 0.2, 0.0, 0.0, 1.0,
	 //왼
	 -0.2, 0.2, -0.2, -1.0, 0.0, 0.0,
	 -0.2, 0.2, 0.2, -1.0, 0.0, 0.0,
	 -0.2, -0.2, 0.2, -1.0, 0.0, 0.0,

	 -0.2, 0.2, -0.2, -1.0, 0.0, 0.0,
	 -0.2, -0.2, 0.2, -1.0, 0.0, 0.0,
	 -0.2, -0.2, -0.2, -1.0, 0.0, 0.0,
	 //오른
	 0.2, -0.2, 0.2, 1.0, 0.0, 0.0,
	 0.2, 0.2, 0.2, 1.0, 0.0, 0.0,
	 0.2, 0.2, -0.2, 1.0, 0.0, 0.0,

	 0.2, -0.2, 0.2, 1.0, 0.0, 0.0,
	 0.2, 0.2, -0.2, 1.0, 0.0, 0.0,
	 0.2, -0.2, -0.2, 1.0, 0.0, 0.0,
	 //위
	 -0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
	 -0.2, 0.2, -0.2, 0.0, 1.0, 0.0,
	 0.2, 0.2, -0.2, 0.0, 1.0, 0.0,

	 0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
	 -0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
	 0.2, 0.2, -0.2, 0.0, 1.0, 0.0,
	 //뒤
	 0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
	 -0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
	 -0.2, -0.2, -0.2, 0.0, 0.0, -1.0,

	 0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
	 -0.2, -0.2, -0.2, 0.0, 0.0, -1.0,
	 0.2, -0.2, -0.2, 0.0, 0.0, -1.0,
	 //밑
	 0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
	 -0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
	 -0.2, -0.2, 0.2, 0.0, -1.0, 0.0,

	 0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
	 -0.2, -0.2, 0.2, 0.0, -1.0, 0.0,
	 0.2, -0.2, 0.2, 0.0, -1.0, 0.0,
	};
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	for (int i = 21; i < 300; i += 20)
	{
		if (nowVertical > i - 0.2f && nowVertical < i + 0.2f
			&& -nowSide < treeSide[i] + 0.1f && -nowSide > treeSide[i] - 0.1f && !isGhost)
		{
			fowardValue = 0.f;
			isOver = true;
		}
		treeTransMatrix = glm::translate(treeTransMatrix, glm::vec3(treeSide[i] - 0.1f + 0.1f, 0.f, -(float)i));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix * treeTransMatrix * treeSideMatrix * treeMatrix));
		glBindVertexArray(VAO[0]);
		glBindTexture(GL_TEXTURE_2D, Textures[22]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		treeTransMatrix = glm::mat4(1.0f);

		if (nowVertical > i - 0.2f && nowVertical < i + 0.2f
			&& -nowSide < treeSide[i] - 0.7f + 0.1f && -nowSide > treeSide[i] - 0.7f - 0.1f && !isGhost)
		{
			fowardValue = 0.f;
			isOver = true;
		}
		treeTransMatrix = glm::translate(treeTransMatrix, glm::vec3(treeSide[i] - 0.7f, 0.f, -(float)i));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix * treeTransMatrix * treeSideMatrix * treeMatrix));
		glBindVertexArray(VAO[0]);
		glBindTexture(GL_TEXTURE_2D, Textures[22]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		treeTransMatrix = glm::mat4(1.0f);
	}
}

void drawCoin()
{
	float coinVertexData[] = {
		//앞
		-0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
		-0.2, 0.2, 0.2, 0.0, 0.0, 1.0,
		0.2, 0.2, 0.2, 0.0, 0.0, 1.0,

		0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
		-0.2, -0.2, 0.2, 0.0, 0.0, 1.0,
		0.2, 0.2, 0.2, 0.0, 0.0, 1.0,
		//왼
		-0.2, 0.2, -0.2, -1.0, 0.0, 0.0,
		-0.2, 0.2, 0.2, -1.0, 0.0, 0.0,
		-0.2, -0.2, 0.2, -1.0, 0.0, 0.0,

		-0.2, 0.2, -0.2, -1.0, 0.0, 0.0,
		-0.2, -0.2, 0.2, -1.0, 0.0, 0.0,
		-0.2, -0.2, -0.2, -1.0, 0.0, 0.0,
		//오른
		0.2, -0.2, 0.2, 1.0, 0.0, 0.0,
		0.2, 0.2, 0.2, 1.0, 0.0, 0.0,
		0.2, 0.2, -0.2, 1.0, 0.0, 0.0,

		0.2, -0.2, 0.2, 1.0, 0.0, 0.0,
		0.2, 0.2, -0.2, 1.0, 0.0, 0.0,
		0.2, -0.2, -0.2, 1.0, 0.0, 0.0,
		//위
		-0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
		-0.2, 0.2, -0.2, 0.0, 1.0, 0.0,
		0.2, 0.2, -0.2, 0.0, 1.0, 0.0,

		0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
		-0.2, 0.2, 0.2, 0.0, 1.0, 0.0,
		0.2, 0.2, -0.2, 0.0, 1.0, 0.0,
		//뒤
		0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
		-0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
		-0.2, -0.2, -0.2, 0.0, 0.0, -1.0,

		0.2, 0.2, -0.2, 0.0, 0.0, -1.0,
		-0.2, -0.2, -0.2, 0.0, 0.0, -1.0,
		0.2, -0.2, -0.2, 0.0, 0.0, -1.0,
		//밑
		0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
		-0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
		-0.2, -0.2, 0.2, 0.0, -1.0, 0.0,

		0.2, -0.2, -0.2, 0.0, -1.0, 0.0,
		-0.2, -0.2, 0.2, 0.0, -1.0, 0.0,
		0.2, -0.2, 0.2, 0.0, -1.0, 0.0,

		//그림자
		-0.2, -0.55, 0.2, 0.0, 0.0, 0.0,
		-0.2, -0.55, -0.2, 0.0, 0.0, 0.0,
		0.2, -0.55, 0.2, 0.0, 0.0, 0.0,
		0.2, -0.55, -0.2, 0.0, 0.0, 0.0,
	};
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]);
	glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(coinVertexData), coinVertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 코인은 자동으로 자신의 y축 기준으로 자전하고 있다.
	coinMatrix = glm::rotate(coinMatrix, glm::radians(2.f), glm::vec3(0.0f, 1.0f, 0.0f));

	for (int i = 0; i < 300; i++)
	{
		if (nowVertical > (float)i - 0.2f && nowVertical < (float)i + 0.2f
			&& -nowSide < coinSide[i] + 0.12f && -nowSide > coinSide[i] - 0.12f && !eatenCoin[i])
		{
			if (eatenCoin[i] == false)
			{
				eatenCoin[i] = true;
				score++;
			}
		}
		if (!eatenCoin[i])
		{
			coinTransMatrix = glm::translate(coinTransMatrix, glm::vec3(coinSide[i], 0.f, -(float)i));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix * coinTransMatrix * coinMatrix));
			glBindVertexArray(VAO[0]);
			glBindTexture(GL_TEXTURE_2D, Textures[18]);

			int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
			glUniform3f(lightPosLocation, 0.f, 0.5, 0.5f);

			int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
			glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

			int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
			glUniform3f(viewPosLocation, 0.0, 0.0, 1.0);

			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindTexture(GL_TEXTURE_2D, Textures[19]);
			glDrawArrays(GL_TRIANGLES, 36, 3);
			glDrawArrays(GL_TRIANGLES, 37, 3);
			coinTransMatrix = glm::mat4(1.0f);
		}
	}
}

void drawSnail()
{
	//스네일은 자전중
	snailMatrix = glm::rotate(snailMatrix, glm::radians(2.f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	for (int i = 10; i < 300; i += 60)
	{
		if (nowVertical > (float)i - 0.2f && nowVertical < (float)i + 0.2f
			&& -nowSide < snailSide[i] + 0.1f && -nowSide > snailSide[i] - 0.1f && !eatenSnail[i])
		{
			eatenSnail[i] = true;
			isSnail = true;
		}
		if (!eatenSnail[i])
		{
			snailTransMatrix = glm::translate(snailTransMatrix, glm::vec3(snailSide[i], 0.f, -(float)i));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix * snailTransMatrix * snailSideMatrix * snailMatrix));
			glBindVertexArray(VAO[0]);
			glBindTexture(GL_TEXTURE_2D, Textures[21]);

			glDrawArrays(GL_TRIANGLES, 0, 36);
			snailTransMatrix = glm::mat4(1.0f);
		}
	}
}

void drawGhost()
{
	//고스트는 자전중
	ghostMatrix = glm::rotate(ghostMatrix, glm::radians(2.f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	for (int i = 40; i < 300; i += 60)
	{
		if (nowVertical > (float)i - 0.2f && nowVertical < (float)i + 0.2f
			&& -nowSide < ghostSide[i] + 0.1f && -nowSide > ghostSide[i] - 0.1f && !eatenGhost[i])
		{
			eatenGhost[i] = true;
			isGhost = true;
		}
		if (!eatenGhost[i])
		{
			ghostTransMatrix = glm::translate(ghostTransMatrix, glm::vec3(ghostSide[i], 0.f, -(float)i));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix * ghostTransMatrix * ghostSideMatrix * ghostMatrix));
			glBindVertexArray(VAO[0]);
			glBindTexture(GL_TEXTURE_2D, Textures[24]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			ghostTransMatrix = glm::mat4(1.0f);
		}
	}
}

void drawMagnet()
{
	//마그넷은 자전중
	magnetMatrix = glm::rotate(magnetMatrix, glm::radians(2.f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	for (int i = 10; i < 300; i += 60)
	{
		if (nowVertical > (float)i - 0.2f && nowVertical < (float)i + 0.2f
			&& -nowSide < magnetSide[i] + 0.1f && -nowSide > magnetSide[i] - 0.1f && !eatenMagnet[i])
		{
			eatenMagnet[i] = true;
			isMagnet = true;
		}
		if (!eatenMagnet[i])
		{
			magnetTransMatrix = glm::translate(magnetTransMatrix, glm::vec3(magnetSide[i], 0.f, -(float)i));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(startAniMatrix * verticalMatrix * sideMatrix * lastMatrix * magnetTransMatrix * magnetSideMatrix * magnetMatrix));
			glBindVertexArray(VAO[0]);
			glBindTexture(GL_TEXTURE_2D, Textures[20]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			magnetTransMatrix = glm::mat4(1.0f);
		}
	}
}

void drawStartButton()
{
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	float floor[] = {
		//start
		-0.4f, 0.1f, 0.f,         0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.4f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.4f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,

		-0.4f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.4f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.4f, -0.1f, 0.f,         1.0f, 0.0f,      0.0f, 1.0f, 0.0f,

		//logo
		-0.4f, 0.2f, 0.f,         0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.4f, -0.2f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.4f, 0.2f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,

		-0.4f, -0.2f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.4f, 0.2f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.4f, -0.2f, 0.f,         1.0f, 0.0f,      0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(4, VBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor), floor, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[0]);
	glBindTexture(GL_TEXTURE_2D, Textures[5]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(defaultMatrix));

	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 999.f, 999.f, 999.f);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
	glUniform3f(viewPosLocation, 999.0, 999.0, 999.0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, Textures[6]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(logoMat));
	glDrawArrays(GL_TRIANGLES, 6, 6);
}

void drawEndButton()
{
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	float floor[] = {
		//start
		-0.4f, 0.1f, 0.f,         0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.4f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.4f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,

		-0.4f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.4f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.4f, -0.1f, 0.f,         1.0f, 0.0f,      0.0f, 1.0f, 0.0f,
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(4, VBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor), floor, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[0]);
	glBindTexture(GL_TEXTURE_2D, Textures[23]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(defaultMatrix));

	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 999.f, 999.f, 999.f);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
	glUniform3f(viewPosLocation, 999.0, 999.0, 999.0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawOverButton()
{
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	float floor[] = {
		//start
		-0.4f, 0.1f, 0.f,         0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.4f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.4f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,

		-0.4f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.4f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.4f, -0.1f, 0.f,         1.0f, 0.0f,      0.0f, 1.0f, 0.0f,
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(4, VBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor), floor, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[0]);
	glBindTexture(GL_TEXTURE_2D, Textures[26]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(defaultMatrix));

	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 999.f, 999.f, 999.f);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
	glUniform3f(viewPosLocation, 999.0, 999.0, 999.0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawScore()
{
	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	float floor[] = {
		//score
		-0.2f, 0.1f, 0.f,         0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.2f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.2f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,

		-0.2f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.2f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.2f, -0.1f, 0.f,         1.0f, 0.0f,      0.0f, 1.0f, 0.0f,

		//num
		-0.05f, 0.1f, 0.f,         0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		-0.05f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.05f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,

		-0.05f, -0.1f, 0.f,         0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
		0.05f, 0.1f, 0.f,         1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
		0.05f, -0.1f, 0.f,         1.0f, 0.0f,      0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(4, VBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor), floor, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//점수:
	glBindVertexArray(VAO[0]);
	glBindTexture(GL_TEXTURE_2D, Textures[7]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(scoreMatrix));

	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 999.f, 999.f, 999.f);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
	glUniform3f(viewPosLocation, 999.0, 999.0, 999.0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//1의자리
	if (score % 10 == 0)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[8]);
	}
	else if (score % 10 == 1)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[9]);
	}
	else if (score % 10 == 2)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[10]);
	}
	else if (score % 10 == 3)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[11]);
	}
	else if (score % 10 == 4)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[12]);
	}
	else if (score % 10 == 5)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[13]);
	}
	else if (score % 10 == 6)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[14]);
	}
	else if (score % 10 == 7)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[15]);
	}
	else if (score % 10 == 8)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[16]);
	}
	else if (score % 10 == 9)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[17]);
	}

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(score1Matrix));
	glDrawArrays(GL_TRIANGLES, 6, 6);

	//10의자리
	if (score / 10 % 10 == 0)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[8]);
	}
	else if (score / 10 % 10 == 1)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[9]);
	}
	else if (score / 10 % 10 == 2)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[10]);
	}
	else if (score / 10 % 10 == 3)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[11]);
	}
	else if (score / 10 % 10 == 4)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[12]);
	}
	else if (score / 10 % 10 == 5)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[13]);
	}
	else if (score / 10 % 10 == 6)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[14]);
	}
	else if (score / 10 % 10 == 7)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[15]);
	}
	else if (score / 10 % 10 == 8)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[16]);
	}
	else if (score / 10 % 10 == 9)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[17]);
	}

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(score10Matrix));
	if (score / 10 != 0)
	{
		glDrawArrays(GL_TRIANGLES, 6, 6);
	}

	//100의자리
	if (score / 100 % 10 == 0)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[8]);
	}
	else if (score / 100 % 10 == 1)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[9]);
	}
	else if (score / 100 % 10 == 2)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[10]);
	}
	else if (score / 100 % 10 == 3)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[11]);
	}
	else if (score / 100 % 10 == 4)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[12]);
	}
	else if (score / 100 % 10 == 5)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[13]);
	}
	else if (score / 100 % 10 == 6)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[14]);
	}
	else if (score / 100 % 10 == 7)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[15]);
	}
	else if (score / 100 % 10 == 8)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[16]);
	}
	else if (score / 100 % 10 == 9)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[17]);
	}

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(score100Matrix));
	if (score / 100 != 0)
	{
		glDrawArrays(GL_TRIANGLES, 6, 6);
	}
}

GLvoid onDisplay() // 콜백 함수: 출력
{
	glUseProgram(programID);

	glClearColor(0.0f, 0.0f, 0.15f, 0.0f); // 채울 배경색을 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //설정된 색으로 배경 칠하기

	unsigned int projectionLocation = glGetUniformLocation(programID, "projectionTransform");

	// Perspective View로 출력
	projection = glm::perspective(glm::radians(45.0f), (float)gwidth / (float)gheight, 0.1f, 100.0f);
	projection = glm::translate(projection, glm::vec3(0.f, 0.f, -2.0f));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	// 게임시작 애니메이션 카메라 값을 갱신한다.
	if (startAni)
	{
		startAniMatrix = glm::mat4(1.0f);
		startAniMatrix = glm::rotate(startAniMatrix, glm::radians(startAniRotValue), glm::vec3(1.0f, 0.0f, 0.0f));
		startAniMatrix = glm::translate(startAniMatrix, glm::vec3(0.f, startAniTransValue, 0.f));
	}

	// 앞으로 이동과 좌우 이동 값을 설정한다.
	verticalMatrix = glm::translate(verticalMatrix, glm::vec3(0.f, 0.f, fowardValue));
	nowVertical += fowardValue;
	sideMatrix = glm::translate(sideMatrix, glm::vec3(sideValue, 0.f, 0.f));
	nowSide += sideValue;

	// 펜스와 충돌
	if (nowSide > sin(PI / 180.0f * nowVertical * 5) * 5 + 2.8f)
	{
		nowSide = sin(PI / 180.0f * nowVertical * 5) * 5 + 2.8f;
		sideValue = -0.1f;
	}
	else if (nowSide < sin(PI / 180.0f * nowVertical * 5) * 5 - 2.8f)
	{
		nowSide = sin(PI / 180.0f * nowVertical * 5) * 5 - 2.8f;
		sideValue = 0.1f;
	}

	// 시작페이지라면 게임 시작 버튼을 출력한다.
	// 시작했다면 스코어를 출력한다.
	// 게임 클리어했다면 클리어 버튼을 출력한다.
	if (isStartPage)
	{
		drawStartButton();
	}
	if (isStart)
	{
		drawScore();
	}
	if (isEnd)
	{
		drawEndButton();
	}
	if (isOver)
	{
		drawOverButton();
		sideValue = 0.f;
		fowardValue = 0.f;
	}

	// 오브젝트들 출력한다.

	drawFence();
	lines();

	if (isGhost)
	{
		glEnable(GL_BLEND);
		glBlendColor(0.2f, 0.5, 0.7f, 0.5f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		drawGae();
		glDisable(GL_BLEND);
	}
	else
	{
		drawGae();
	}

	drawCoin();
	drawGhost();
	drawSnail();
	drawMagnet();
	drawTree();

	glutSwapBuffers();
}

GLvoid onReshape(int w, int h) // 콜백 함수: 다시 그리기
{
	gwidth = w;
	gheight = h;
	glViewport(0, 0, w, h);
}

int main(int argc, char** argv) // 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이모드 설정
	glutCreateWindow("GaeSki"); // 윈도우 생성(윈도우 이름)
	glutFullScreen(); // 풀스크린 모드

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		cerr << "Unable to initialize GLEW" << endl;
		exit(-1);
	}
	else
	{
		cout << "GLEW Initialized\n\n";
		cout << "GAME START!\n";
	}

	Init();
	InitTexture();

	glutDisplayFunc(onDisplay); // 출력 함수의 지정
	glutReshapeFunc(onReshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);

	glutMainLoop(); // 이벤트 처리 시작
}
