# TsfPad rendered with direct2d

![](https://i.postimg.cc/qvX57tBh/Snipaste-2025-07-20-14-15-18.png)

![](https://i.postimg.cc/bvmVQKtq/Snipaste-2025-07-20-14-15-38.png)

![](https://i.postimg.cc/wjdrH5zY/Snipaste-2025-07-20-14-15-56.png)

![](https://i.postimg.cc/fbzgSwkH/Snipaste-2025-07-20-14-16-24.png)

## How to build and run

Prerequisites:

- Visual Studio 2022
- Windows SDK
- vcpkg
- CMake
- Python 3.10+
- Scoop

And make sure your vcpkg is installed by scoop.

Run the following commands in the pwsh7:

```powershell
git clone https://github.com/fanlumaster/TsfPad.git
cd TsfPad
python .\scripts\prepare_env.py
.\scripts\lcompile.ps1
.\build\bin\Debug\TsfPad.exe
```

## References

- <https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/winui/input/tsf/tsfapps/tsfpad-step4>
