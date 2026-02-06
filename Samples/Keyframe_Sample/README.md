# GCProjectTemplate
* GCRuntime 을 사용하여 실행파일을 구성하는 프로젝트

# 동작 방법
* 스튜디오에서 새로운 프로젝트를 생성하면 .vscode 폴더 및 설정파일과 src/AppMain.cpp 파일을 프로젝트로 복사한다.
* 사용자가 Build 혹은 누르면 해당 Project 의 Root 폴더를 기준으로 vscode 가 열린다.

## 프로젝트 위치
* C:\GrapiCarStudio\Workspace\gcprojecttemplate
## Runtime 위치
* C:\GrapiCarStudio\runtime

# 컴파일
## cmake 빌드
### Debug/Release 전환
1. Ctrl + Shift + P 
2. CMake: 구성 사전 설정 선택
3. "Windows MSVC x64 Debug" 혹은 "Windows MSVC x64 Release" 선택

### 디버그/시작 프로그램 설정
* 디버그 할 프로그램 선택
1. Ctrl + Shift + P 
2. CMake: 디버그/시작 대상 설정 선택
3. 원하는 프로젝트 선택

### 빌드
* 하단 톱니 아이콘의 빌드 버튼 클릭
p
### 디버그 실행
* 하단 벌레 아이콘 클릭

### 실행
* 하단 삼각형 아이콘 클릭

## vscode 의 tasks.json 기반 빌드
### vscode 에서 빌드 (사용자가 직접 빌드를 할 때)
* Ctrl + Shift + B : Debug, Release 빌드 선택

### cmake 에서 빌드 (추후 스튜디오에서 빌드만 실행할 때 사용)
* ~\gcprojecttemplate> mkdir build
* ~\gcprojecttemplate> cd build
* ~\gcprojecttemplate\build> cmake .. -DCMAKE_BUILD_TYPE=Debug
* ~\gcprojecttemplate\build> cmake --build . --config Debug

### 실행
* Ctrl + F5

### 솔루션 정리
* Ctrt + Shift + P
* 'Tasks: Run Task' 선택
* '솔루션 정리 (MSVC)' 선택

