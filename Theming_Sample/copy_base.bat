@echo off
REM 현재 배치파일이 위치한 Debug 폴더 기준으로 상위 폴더로 이동
set "SRC_DBG_DIR=%~dp0\..\..\runtime\lib\engine\x86_64\Debug\"
set "SRC_REL_DIR=%~dp0\..\..\runtime\lib\engine\x86_64\Release\"
set "DST_DBG_DIR=%~dp0\Debug\"
set "DST_REL_DIR=%~dp0\Release\"

REM 소스와 대상 파일 설정
set "SRC_DBG_FILE=%SRC_DBG_DIR%grapi-base.dll"
set "DST_DBG_FILE=%DST_DBG_DIR%grapi-base.dll"

set "SRC_REL_FILE=%SRC_REL_DIR%grapi-base.dll"
set "DST_REL_FILE=%DST_REL_DIR%grapi-base.dll"

REM 대상 폴더가 없다면 생성
if not exist "%DST_DBG_DIR%" (
    mkdir "%DST_DGB_DIR%"
)
if not exist "%DST_REL_DIR%" (
    mkdir "%DST_REL_DIR%"
)

REM 파일 복사
copy /Y "%SRC_DBG_FILE%" "%DST_DBG_FILE%"
copy /Y "%SRC_REL_FILE%" "%DST_REL_FILE%"
echo base.dll 복사가 완료되었습니다.

REM pause
