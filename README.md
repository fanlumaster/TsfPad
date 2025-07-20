# TsfPad

Original repo: <https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/winui/input/tsf/tsfapps/tsfpad-step4>

![](https://i.postimg.cc/DfjCHdWz/Snipaste-2025-07-20-02-01-07.png)

![](https://i.postimg.cc/YqvXHGgz/Snipaste-2025-07-20-02-01-31.png)

![](https://i.postimg.cc/d3x4CwMC/Snipaste-2025-07-20-02-10-09.png)

## How to build and run

Prerequisites:

- Visual Studio 2022
- Windows SDK
- vcpkg
- CMake
- Python 3.10+

Run the following commands in the pwsh7:

```powershell
git clone https://github.com/fanlumaster/TsfPad.git
cd TsfPad
python .\scripts\prepare_env.py
.\scripts\lcompile.ps1
.\build\bin\Debug\TsfPad.exe
```
