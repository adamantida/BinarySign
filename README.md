# File Signature Tool

This repository contains a simple C++ application to add and verify a signature to/from a file. The signature is a base64-encoded comment that is appended to the file. 

## Features

- **Add Signature**: Append a base64-encoded comment to the end of a file.
- **Verify Signature**: Check for and decode the base64-encoded comment from a file.

## Requirements

- C++11 or later
- A base64 library (included as `base64.h`)

## Usage

### Adding a Signature

To add a signature to a file, use the `-i` flag for the input file, the `-o` flag for the output file, and the `-c` flag for the comment to be encoded and appended.

```bash
BinarySign.exe -i <input_file> -o <output_file> -c <comment>
```
### Verifying a Signature

To verify a signature from a file, use the -v flag followed by the file name.
```bash
BinarySign.exe -v <file>
```

### Example
#### Adding a Signature
```bash
BinarySign.exe -i example.* -o signed_example.* -c "This is a test comment"
```
#### Verifying a Signature
```bash
BinarySign.exe -v signed_example.*
```
