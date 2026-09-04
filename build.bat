@echo off
echo ===================================================
echo   Compilando Snake Game em C...
echo ===================================================

:: Tenta localizar GCC no PATH
where gcc >nul 2>nul
if %errorlevel% equ 0 (
    echo Usando GCC encontrado no PATH...
    gcc -O2 -Wall main.c game.c -o snake.exe
    goto check_result
)

:: Tenta localizar Clang no PATH
where clang >nul 2>nul
if %errorlevel% equ 0 (
    echo Usando Clang encontrado no PATH...
    clang -O2 -Wall main.c game.c -o snake.exe
    goto check_result
)

:: Tenta encontrar compilador LLVM-MinGW no WinGet Temp
for /r "%LOCALAPPDATA%\Temp\WinGet" %%i in (clang.exe) do (
    if exist "%%i" (
        echo Usando Clang do WinGet: %%i
        "%%i" -O2 -Wall main.c game.c -o snake.exe
        goto check_result
    )
)

:: Tenta encontrar compiladores MinGW instalados no WinGet / APPDATA
for /r "%LOCALAPPDATA%\Microsoft\WinGet\Packages" %%i in (gcc.exe) do (
    if exist "%%i" (
        echo Usando GCC WinGet: %%i
        "%%i" -O2 -Wall main.c game.c -o snake.exe
        goto check_result
    )
)

:: Tenta encontrar MSYS2 gcc
if exist "C:\msys64\ucrt64\bin\gcc.exe" (
    echo Usando MSYS2 GCC...
    C:\msys64\ucrt64\bin\gcc.exe -O2 -Wall main.c game.c -o snake.exe
    goto check_result
)

echo [ERRO] NENHUM COMPILADOR C ENCONTRADO NO SISTEMA!
echo Instale o MinGW / GCC ou adicione o compilador ao seu PATH.
pause
exit /b 1

:check_result
if %errorlevel% equ 0 (
    echo ===================================================
    echo  COMPILADO COM SUCESSO! Executavel criado: snake.exe
    echo ===================================================
) else (
    echo ===================================================
    echo  [ERRO] FALHA NA COMPILACAO.
    echo ===================================================
)
