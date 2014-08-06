//
// TMidasFile.h.
//

#ifndef TMIDASFILE_H
#define TMIDASFILE_H

#include <string>

#include <TObject.h>

class TMidasEvent;

/// Reader for MIDAS .mid files

class TMidasFile : public TObject
{
public:
  TMidasFile(); ///< default constructor
  ~TMidasFile(); ///< destructor

  bool Open(const char* filename); ///< Open input file
  bool OutOpen(const char* filename); ///< Open output file

  void Close(); ///< Close input file
  void OutClose(); ///< Close output file

  int  Read(TMidasEvent *event); ///< Read one event from the file
  bool Write(TMidasEvent *event); ///< Write one event to the output file

  const char* GetFilename()  const { return fFilename.c_str();  } ///< Get the name of this file
  int         GetLastErrno() const { return fLastErrno; }         ///< Get error value for the last file error
  const char* GetLastError() const { return fLastError.c_str(); } ///< Get error text for the last file error

	int	GetRunNumber();
  int	GetSubRunNumber();

protected:

  std::string fFilename; ///< name of the currently open file
  std::string fOutFilename; ///< name of the currently open file

  int         fLastErrno; ///< errno from the last operation
  std::string fLastError; ///< error string from last errno

  bool fDoByteSwap; ///< "true" if file has to be byteswapped

  int         fFile; ///< open input file descriptor
  void*       fGzFile; ///< zlib compressed input file reader
  void*       fPoFile; ///< popen() input file reader
  int         fOutFile; ///< open output file descriptor
  void*       fOutGzFile; ///< zlib compressed output file reader

	ClassDef(TMidasFile,0)
};

#endif // TMidasFile.h
