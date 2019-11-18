Requires:
 
- Visual Studio 2019 free version
 

- vcpkg which is found here: https://github.com/Microsoft/vcpkg
 
  help here: https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md

- follow the install instructions which basically is to download and run:  .\bootstrap-vcpkg.bat using powershell
 

- install opencv4 (4.1.2) 32bits and 64bits just in case someone needs 32bits.
	from power shell:
    
	for 32 bits:
      
		.\vcpkg.exe install opencv4
    
	for 64 bits: 
     
		.\vcpkg.exe install opencv4:x64-windows
     
 

- incorporate the packages into visual studio:
     
	.\vcpkg.exe integrate install

