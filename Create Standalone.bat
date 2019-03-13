rmdir /S /Q Standalone
mkdir Standalone
cd Standalone
mkdir DigiPengs
xcopy /Y ..\Debug\DigitalPenguins.exe DigiPengs
xcopy /Y ..\Debug\*.dll DigiPengs
xcopy /I /S /Y ..\Assets DigiPengs\Assets