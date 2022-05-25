# [amlogic-usbdl](https://github.com/frederic/amlogic-usbdl) : unsigned code loader for Amlogic bootrom

## Disclaimer
You will be solely responsible for any damage caused to your hardware/software/warranty/data/cat/etc...

## Description
Amlogic bootrom supports booting from USB. This method of boot requires an USB host to send a signed bootloader to the bootrom via USB port.  This fork is modified to work with the S922X SOC.

This tool exploits a [vulnerability](https://fredericb.info/2021/02/amlogic-usbdl-unsigned-code-loader-for-amlogic-bootrom.html) in the USB download mode to load and run unsigned code in Secure World.

## Supported targets
* Odroid N2+ (S922X) (Secure boot is disabled anyway)
* Amazon FireTV 2nd gen Cube (S922X)

## Usage
```
./amlogic-usbdl <input_file> [<output_file>]
	input_file: payload binary to load and execute (max size 65282 bytes)
	output_file: file to write data returned by payload
```
Note: payload binary size can be increased to a maximum of 65530 bytes, by decreasing the bulk_transfer_count in amlogic-usbdl to 0x6. 

## Payloads
Payloads are raw binary AArch64 executables. Some are provided in directory **payloads/**.

## License
Please see [LICENSE](/LICENSE).
