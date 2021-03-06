//
// File generated by rootcint at Wed Jun 25 13:49:26 2014

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME TMidasFileDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "TMidasFileDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void TMidasFile_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_TMidasFile(void *p = 0);
   static void *newArray_TMidasFile(Long_t size, void *p);
   static void delete_TMidasFile(void *p);
   static void deleteArray_TMidasFile(void *p);
   static void destruct_TMidasFile(void *p);
   static void streamer_TMidasFile(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMidasFile*)
   {
      ::TMidasFile *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMidasFile >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMidasFile", ::TMidasFile::Class_Version(), "./../include/TMidasFile.h", 17,
                  typeid(::TMidasFile), DefineBehavior(ptr, ptr),
                  &::TMidasFile::Dictionary, isa_proxy, 0,
                  sizeof(::TMidasFile) );
      instance.SetNew(&new_TMidasFile);
      instance.SetNewArray(&newArray_TMidasFile);
      instance.SetDelete(&delete_TMidasFile);
      instance.SetDeleteArray(&deleteArray_TMidasFile);
      instance.SetDestructor(&destruct_TMidasFile);
      instance.SetStreamerFunc(&streamer_TMidasFile);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMidasFile*)
   {
      return GenerateInitInstanceLocal((::TMidasFile*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMidasFile*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *TMidasFile::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *TMidasFile::Class_Name()
{
   return "TMidasFile";
}

//______________________________________________________________________________
const char *TMidasFile::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMidasFile*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMidasFile::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMidasFile*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void TMidasFile::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMidasFile*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *TMidasFile::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMidasFile*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void TMidasFile::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMidasFile.

   TObject::Streamer(R__b);
}

//______________________________________________________________________________
void TMidasFile::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class TMidasFile.
      TClass *R__cl = ::TMidasFile::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fFilename", (void*)&fFilename);
      R__insp.InspectMember("string", (void*)&fFilename, "fFilename.", false);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fOutFilename", (void*)&fOutFilename);
      R__insp.InspectMember("string", (void*)&fOutFilename, "fOutFilename.", false);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fLastErrno", &fLastErrno);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fLastError", (void*)&fLastError);
      R__insp.InspectMember("string", (void*)&fLastError, "fLastError.", false);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fDoByteSwap", &fDoByteSwap);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fFile", &fFile);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*fGzFile", &fGzFile);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*fPoFile", &fPoFile);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fOutFile", &fOutFile);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*fOutGzFile", &fOutGzFile);
      TObject::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMidasFile(void *p) {
      return  p ? new(p) ::TMidasFile : new ::TMidasFile;
   }
   static void *newArray_TMidasFile(Long_t nElements, void *p) {
      return p ? new(p) ::TMidasFile[nElements] : new ::TMidasFile[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMidasFile(void *p) {
      delete ((::TMidasFile*)p);
   }
   static void deleteArray_TMidasFile(void *p) {
      delete [] ((::TMidasFile*)p);
   }
   static void destruct_TMidasFile(void *p) {
      typedef ::TMidasFile current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TMidasFile(TBuffer &buf, void *obj) {
      ((::TMidasFile*)obj)->::TMidasFile::Streamer(buf);
   }
} // end of namespace ROOT for class ::TMidasFile

/********************************************************
* TMidasFileDict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableTMidasFileDict();

extern "C" void G__set_cpp_environmentTMidasFileDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("../include/TMidasFile.h");
  G__cpp_reset_tagtableTMidasFileDict();
}
#include <new>
extern "C" int G__cpp_dllrevTMidasFileDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* TMidasFile */
static int G__TMidasFileDict_169_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TMidasFile* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new TMidasFile[n];
     } else {
       p = new((void*) gvp) TMidasFile[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new TMidasFile;
     } else {
       p = new((void*) gvp) TMidasFile;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((TMidasFile*) G__getstructoffset())->Open((const char*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((TMidasFile*) G__getstructoffset())->OutOpen((const char*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TMidasFile*) G__getstructoffset())->Close();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TMidasFile*) G__getstructoffset())->OutClose();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TMidasFile*) G__getstructoffset())->Read((TMidasEvent*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((TMidasFile*) G__getstructoffset())->Write((TMidasEvent*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) ((const TMidasFile*) G__getstructoffset())->GetFilename());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((const TMidasFile*) G__getstructoffset())->GetLastErrno());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) ((const TMidasFile*) G__getstructoffset())->GetLastError());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TMidasFile*) G__getstructoffset())->GetRunNumber());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TMidasFile*) G__getstructoffset())->GetSubRunNumber());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) TMidasFile::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TMidasFile::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) TMidasFile::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      TMidasFile::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TMidasFile*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TMidasFile::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) TMidasFile::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TMidasFile::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMidasFileDict_169_0_24(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) TMidasFile::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__TMidasFileDict_169_0_25(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   TMidasFile* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new TMidasFile(*(TMidasFile*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef TMidasFile G__TTMidasFile;
static int G__TMidasFileDict_169_0_26(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (TMidasFile*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((TMidasFile*) (soff+(sizeof(TMidasFile)*i)))->~G__TTMidasFile();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (TMidasFile*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((TMidasFile*) (soff))->~G__TTMidasFile();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__TMidasFileDict_169_0_27(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TMidasFile* dest = (TMidasFile*) G__getstructoffset();
   *dest = *(TMidasFile*) libp->para[0].ref;
   const TMidasFile& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* TMidasFile */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncTMidasFileDict {
 public:
  G__Sizep2memfuncTMidasFileDict(): p(&G__Sizep2memfuncTMidasFileDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncTMidasFileDict::*p)();
};

size_t G__get_sizep2memfuncTMidasFileDict()
{
  G__Sizep2memfuncTMidasFileDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceTMidasFileDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile))) {
     TMidasFile *G__Lderived;
     G__Lderived=(TMidasFile*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile),G__get_linked_tagnum(&G__TMidasFileDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableTMidasFileDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__TMidasFileDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TMidasFileDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMidasFileDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TMidasFileDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMidasFileDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__TMidasFileDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TMidasFileDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMidasFileDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TMidasFileDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMidasFileDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* TMidasFile */
static void G__setup_memvarTMidasFile(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile));
   { TMidasFile *p; p=(TMidasFile*)0x1000; if (p) { }
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__TMidasFileDictLN_string),-1,-1,2,"fFilename=",0,"/< name of the currently open file");
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__TMidasFileDictLN_string),-1,-1,2,"fOutFilename=",0,"/< name of the currently open file");
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"fLastErrno=",0,"/< errno from the last operation");
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__TMidasFileDictLN_string),-1,-1,2,"fLastError=",0,"/< error string from last errno");
   G__memvar_setup((void*)0,103,0,0,-1,-1,-1,2,"fDoByteSwap=",0,"/< \"true\" if file has to be byteswapped");
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"fFile=",0,"/< open input file descriptor");
   G__memvar_setup((void*)0,89,0,0,-1,-1,-1,2,"fGzFile=",0,"/< zlib compressed input file reader");
   G__memvar_setup((void*)0,89,0,0,-1,-1,-1,2,"fPoFile=",0,"/< popen() input file reader");
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"fOutFile=",0,"/< open output file descriptor");
   G__memvar_setup((void*)0,89,0,0,-1,-1,-1,2,"fOutGzFile=",0,"/< zlib compressed output file reader");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__TMidasFileDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarTMidasFileDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncTMidasFile(void) {
   /* TMidasFile */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile));
   G__memfunc_setup("TMidasFile",962,G__TMidasFileDict_169_0_1, 105, G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile), -1, 0, 0, 1, 1, 0, "", "/< default constructor", (void*) NULL, 0);
   G__memfunc_setup("Open",402,G__TMidasFileDict_169_0_2, 103, -1, -1, 0, 1, 1, 1, 0, "C - - 10 - filename", "/< Open input file", (void*) NULL, 0);
   G__memfunc_setup("OutOpen",714,G__TMidasFileDict_169_0_3, 103, -1, -1, 0, 1, 1, 1, 0, "C - - 10 - filename", "/< Open output file", (void*) NULL, 0);
   G__memfunc_setup("Close",502,G__TMidasFileDict_169_0_4, 121, -1, -1, 0, 0, 1, 1, 0, "", "/< Close input file", (void*) NULL, 0);
   G__memfunc_setup("OutClose",814,G__TMidasFileDict_169_0_5, 121, -1, -1, 0, 0, 1, 1, 0, "", "/< Close output file", (void*) NULL, 0);
   G__memfunc_setup("Read",380,G__TMidasFileDict_169_0_6, 105, -1, -1, 0, 1, 1, 1, 0, "U 'TMidasEvent' - 0 - event", "/< Read one event from the file", (void*) NULL, 0);
   G__memfunc_setup("Write",523,G__TMidasFileDict_169_0_7, 103, -1, -1, 0, 1, 1, 1, 0, "U 'TMidasEvent' - 0 - event", "/< Write one event to the output file", (void*) NULL, 0);
   G__memfunc_setup("GetFilename",1089,G__TMidasFileDict_169_0_8, 67, -1, -1, 0, 0, 1, 1, 9, "", "/< Get the name of this file", (void*) NULL, 0);
   G__memfunc_setup("GetLastErrno",1210,G__TMidasFileDict_169_0_9, 105, -1, -1, 0, 0, 1, 1, 8, "", "/< Get error value for the last file error", (void*) NULL, 0);
   G__memfunc_setup("GetLastError",1214,G__TMidasFileDict_169_0_10, 67, -1, -1, 0, 0, 1, 1, 9, "", "/< Get error text for the last file error", (void*) NULL, 0);
   G__memfunc_setup("GetRunNumber",1214,G__TMidasFileDict_169_0_11, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetSubRunNumber",1512,G__TMidasFileDict_169_0_12, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__TMidasFileDict_169_0_13, 85, G__get_linked_tagnum(&G__TMidasFileDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&TMidasFile::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__TMidasFileDict_169_0_14, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TMidasFile::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__TMidasFileDict_169_0_15, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&TMidasFile::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__TMidasFileDict_169_0_16, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&TMidasFile::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__TMidasFileDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__TMidasFileDict_169_0_20, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__TMidasFileDict_169_0_21, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TMidasFile::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__TMidasFileDict_169_0_22, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&TMidasFile::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__TMidasFileDict_169_0_23, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TMidasFile::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__TMidasFileDict_169_0_24, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&TMidasFile::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("TMidasFile", 962, G__TMidasFileDict_169_0_25, (int) ('i'), G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile), -1, 0, 1, 1, 1, 0, "u 'TMidasFile' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~TMidasFile", 1088, G__TMidasFileDict_169_0_26, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__TMidasFileDict_169_0_27, (int) ('u'), G__get_linked_tagnum(&G__TMidasFileDictLN_TMidasFile), -1, 1, 1, 1, 1, 0, "u 'TMidasFile' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncTMidasFileDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
}

static void G__cpp_setup_global2() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalTMidasFileDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
  G__cpp_setup_global2();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcTMidasFileDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__TMidasFileDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_string = { "string" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_TMidasEvent = { "TMidasEvent" , 99 , -1 };
G__linked_taginfo G__TMidasFileDictLN_TMidasFile = { "TMidasFile" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableTMidasFileDict() {
  G__TMidasFileDictLN_TClass.tagnum = -1 ;
  G__TMidasFileDictLN_TBuffer.tagnum = -1 ;
  G__TMidasFileDictLN_TMemberInspector.tagnum = -1 ;
  G__TMidasFileDictLN_TObject.tagnum = -1 ;
  G__TMidasFileDictLN_string.tagnum = -1 ;
  G__TMidasFileDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__TMidasFileDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TMidasFileDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__TMidasFileDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TMidasFileDictLN_TMidasEvent.tagnum = -1 ;
  G__TMidasFileDictLN_TMidasFile.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableTMidasFileDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_string);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_TMidasEvent);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__TMidasFileDictLN_TMidasFile),sizeof(TMidasFile),-1,29952,(char*)NULL,G__setup_memvarTMidasFile,G__setup_memfuncTMidasFile);
}
extern "C" void G__cpp_setupTMidasFileDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupTMidasFileDict()");
  G__set_cpp_environmentTMidasFileDict();
  G__cpp_setup_tagtableTMidasFileDict();

  G__cpp_setup_inheritanceTMidasFileDict();

  G__cpp_setup_typetableTMidasFileDict();

  G__cpp_setup_memvarTMidasFileDict();

  G__cpp_setup_memfuncTMidasFileDict();
  G__cpp_setup_globalTMidasFileDict();
  G__cpp_setup_funcTMidasFileDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncTMidasFileDict();
  return;
}
class G__cpp_setup_initTMidasFileDict {
  public:
    G__cpp_setup_initTMidasFileDict() { G__add_setup_func("TMidasFileDict",(G__incsetup)(&G__cpp_setupTMidasFileDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initTMidasFileDict() { G__remove_setup_func("TMidasFileDict"); }
};
G__cpp_setup_initTMidasFileDict G__cpp_setup_initializerTMidasFileDict;

