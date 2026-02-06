@echo off
setlocal

REM 현재 배치 파일의 경로 기준으로 디렉터리 설정
set BASE_DIR=%~dp0
set DEBUG_DIR=%BASE_DIR%Debug
set RELEASE_DIR=%BASE_DIR%Release

REM Debug 폴더 삭제
if exist "%DEBUG_DIR%" (
    echo Debug 폴더 삭제 중...
    rmdir /S /Q "%DEBUG_DIR%"
) else (
    echo Debug 폴더가 존재하지 않습니다.
)

REM Release 폴더 삭제
if exist "%RELEASE_DIR%" (
    echo Release 폴더 삭제 중...
    rmdir /S /Q "%RELEASE_DIR%"
) else (
    echo Release 폴더가 존재하지 않습니다.
)

REM echo ✅ 삭제 작업 완료!
REM pause
endlocal
