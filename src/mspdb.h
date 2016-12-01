// Convert DMD CodeView debug information to PDB files
// Copyright (c) 2009-2010 by Rainer Schuetze, All Rights Reserved
//
// License for redistribution is given by the Artistic License 2.0
// see file LICENSE for further details

#ifndef __MSPDB_H__
#define __MSPDB_H__

#include <stdio.h>

struct _GUID;

namespace mspdb
{

struct MREUtil;
struct MREFile;
struct MREBag;
struct BufferDefaultAllocator;
struct EnumSC;
struct Stream;
struct EnumThunk;
struct EnumSyms;
struct EnumLines;
struct Dbg;
struct EnumSrc;
struct MREDrv;
struct MREngine;
struct EnumNameMap_Special;
struct MRECmp2;
struct PDB;
struct Src;
struct Mod;
struct StreamCached;
struct GSI;
struct TPI;
struct IPI;
struct NameMap;
struct EnumNameMap;
struct DBI;

enum EnumType : int;
enum DEPON : int;
enum YNM : int;
enum TrgType : int;
enum PCC : int;
enum DBGTYPE : int;
enum DOVC : int;

extern int vsVersion;

/*
#define DBICommon DBI
#define DBI2 DBI
*/

struct MREUtil {
	virtual int FRelease(void);
	virtual void EnumSrcFiles(int (__stdcall*)(struct MREUtil *,struct EnumFile &,enum EnumType),unsigned short const *,void *);
	virtual void EnumDepFiles(struct EnumFile &,int (__stdcall*)(struct MREUtil *,struct EnumFile &,enum EnumType));
	virtual void EnumAllFiles(int (__stdcall*)(struct MREUtil *,struct EnumFile &),unsigned short const *,void *);
	virtual void Enumstructes(int (__stdcall*)(struct MREUtil *,struct Enumstruct &),unsigned short const *,void *);
	virtual void SummaryStats(struct MreStats &);
};

struct MREFile {
	virtual int FOpenBag(struct MREBag * *,unsigned long);
	virtual int FnoteEndInclude(unsigned long);
	virtual int FnotestructMod(unsigned long,unsigned long);
	virtual int FnoteInlineMethodMod(unsigned long,char const *,unsigned long);
	virtual int FnoteLineDelta(unsigned long,int);
	virtual void EnumerateChangedstructes(int (__cdecl*)(unsigned long,struct MREFile *,int (*)(unsigned long,unsigned long)));
	virtual int FnotestructTI(unsigned long,unsigned long);
	virtual int FIsBoring(void);
	virtual int FnotePchCreateUse(unsigned short const *,unsigned short const *);
};

struct MREBag {
	virtual int FAddDep(unsigned long,unsigned long,char const *,enum DEPON,unsigned long);
	virtual int FClose(void);
};

struct BufferDefaultAllocator {
	virtual unsigned char * Alloc(long);
	virtual unsigned char * AllocZeroed(long);
	virtual void DeAlloc(unsigned char *);
};

struct EnumSC {
	virtual int next(void);
	virtual void get(unsigned short *,unsigned short *,long *,long *,unsigned long *);
	virtual void getCrcs(unsigned long *,unsigned long *);
	virtual bool fUpdate(long,long);
	virtual int prev(void);
	virtual int clone(struct EnumContrib * *);
	virtual int locate(long,long);
};

struct Stream {
	virtual long QueryCb(void);
	virtual int Read(long,void *,long *);
	virtual int Write(long,void *,long);
	virtual int Replace(void *,long);
	virtual int Append(void *,long);
	virtual int Delete(void);
	virtual int Release(void);
	virtual int Read2(long,void *,long);
	virtual int Truncate(long);
};

struct EnumThunk {
	virtual void release(void);
	virtual void reset(void);
	virtual int next(void);
	virtual void get(unsigned short *,long *,long *);
};

struct EnumSyms {
	virtual void release(void);
	virtual void reset(void);
	virtual int next(void);
	virtual void get(unsigned char * *);
	virtual int prev(void);
	virtual int clone(struct EnumSyms * *);
	virtual int locate(long,long);
};

struct EnumLines {
	virtual void release(void);
	virtual void reset(void);
	virtual int next(void);
	virtual bool getLines(unsigned long *,unsigned long *,unsigned short *,unsigned long *,unsigned long *,struct CV_Line_t *);
	virtual bool getLinesColumns(unsigned long *,unsigned long *,unsigned short *,unsigned long *,unsigned long *,struct CV_Line_t *,struct CV_Column_t *);
	virtual bool clone(struct EnumLines * *);
};

struct Dbg {
	virtual int Close(void);
	virtual long QuerySize(void);
	virtual void Reset(void);
	virtual int Skip(unsigned long);
	virtual int QueryNext(unsigned long,void *);
	virtual int Find(void *);
	virtual int Clear(void);
	virtual int Append(unsigned long,void const *);
	virtual int ReplaceNext(unsigned long,void const *);
	virtual int Clone(struct Dbg * *);
	virtual long QueryElementSize(void);
};

struct EnumSrc {
	virtual void release(void);
	virtual void reset(void);
	virtual int next(void);
	virtual void get(struct SrcHeaderOut const * *);
};

struct MREDrv {
	virtual int FRelease(void);
	virtual int FRefreshFileSysInfo(void);
	virtual int FSuccessfulCompile(int,unsigned short const *,unsigned short const *);
	virtual enum YNM YnmFileOutOfDate(struct SRCTARG &);
	virtual int FFilesOutOfDate(struct CAList *);
	virtual int FUpdateTargetFile(unsigned short const *,enum TrgType);
	virtual void OneTimeInit(void);
};

struct MREngine {
	virtual int FDelete(void);
	virtual int FClose(int);
	virtual void QueryPdbApi(struct PDB * &,struct NameMap * &);
	virtual void _Reserved_was_QueryMreLog(void);
	virtual void QueryMreDrv(struct MREDrv * &);
	virtual void QueryMreCmp(struct MRECmp2 * &,struct TPI *);
	virtual void QueryMreUtil(struct MREUtil * &);
	virtual int FCommit(void);
};

struct MRECmp2 {
	virtual int FRelease(void);
	virtual int FOpenCompiland(struct MREFile * *,unsigned short const *,unsigned short const *);
	virtual int FCloseCompiland(struct MREFile *,int);
	virtual int FPushFile(struct MREFile * *,unsigned short const *,void *);
	virtual struct MREFile * PmrefilePopFile(void);
	virtual int FStoreDepData(struct DepData *);
	virtual int FRestoreDepData(struct DepData *);
	virtual void structIsBoring(unsigned long);
};

//    virtual void * Pool<16384>::AllocBytes(unsigned int);
//    virtual void EnumSyms::get(unsigned char * *);
//    virtual void * Pool<65536>::AllocBytes(unsigned int);
//    virtual void EnumSyms::get(unsigned char * *);

typedef int __cdecl fnPDBOpen2W(const wchar_t *path,char const *mode,long *p,
				wchar_t *ext,unsigned int flags,struct PDB **pPDB);

struct PDB_part1 {
	virtual unsigned long QueryInterfaceVersion(void);
	virtual unsigned long QueryImplementationVersion(void);
	virtual long QueryLastError(char * const);
	virtual char * QueryPDBName(char * const);
	virtual unsigned long QuerySignature(void);
	virtual unsigned long QueryAge(void);
	virtual int CreateDBI(char const *,struct DBI * *);
	virtual int OpenDBI(char const *,char const *,struct DBI * *);
	virtual int OpenTpi(char const *,struct TPI * *);
};

struct PDB_part_vs11 : public PDB_part1 {
	virtual int OpenIpi(char const *,struct IPI * *); // VS11
};

template<typename BASE>
struct PDB_part2 : public BASE {
	virtual int Commit(void);
	virtual int Close(void);
	virtual int OpenStreamW(unsigned short const *,struct Stream * *);
	virtual int GetEnumStreamNameMap(struct Enum * *);
	virtual int GetRawBytes(int (__cdecl*)(void const *,long));
	virtual unsigned long QueryPdbImplementationVersion(void);
	virtual int OpenDBIEx(char const *,char const *,struct DBI * *,int (__stdcall*)(struct _tagSEARCHDEBUGINFO *));
	virtual int CopyTo(char const *,unsigned long,unsigned long);
	virtual int OpenSrc(struct Src * *);
	virtual long QueryLastErrorExW(unsigned short *,unsigned int);
	virtual unsigned short * QueryPDBNameExW(unsigned short *,unsigned int);
	virtual int QuerySignature2(struct _GUID *);
	virtual int CopyToW(unsigned short const *,unsigned long,unsigned long);
	virtual int fIsSZPDB(void)const ;
	virtual int containsW(unsigned short const *,unsigned long *);
	virtual int CopyToW2(unsigned short const *,unsigned long,int (__cdecl*(__cdecl*)(void *,enum PCC))(void),void *);
	virtual int OpenStreamEx(char const *,char const *,struct Stream * *);
};

struct PDB_VS10 : public PDB_part2<PDB_part1> {};
struct PDB_VS11 : public PDB_part2<PDB_part_vs11> {};

struct PDB
{
	PDB_VS10 vs10;

	static int __cdecl Open2W(unsigned short const *path,char const *mode,long *p,unsigned short *ext,unsigned int flags,struct PDB **pPDB);

	unsigned long QueryAge() { return vs10.QueryAge(); }
	int CreateDBI(char const *n,struct DBI * *pdbi) { return vs10.CreateDBI(n, pdbi); }
	int OpenTpi(char const *n,struct TPI * *ptpi)  { return vs10.OpenTpi(n, ptpi); }
	long QueryLastError(char * const lastErr) { return vs10.QueryLastError(lastErr); }

	int Commit()
	{
		if(vsVersion >= 11)
			return ((PDB_VS11*)&vs10)->Commit();
		return vs10.Commit();
	}
	int Close()
	{
		if(vsVersion >= 11)
			return ((PDB_VS11*)&vs10)->Close();
		return vs10.Close();
	}
	int QuerySignature2(struct _GUID *guid)
	{
		if(vsVersion >= 11)
			return ((PDB_VS11*)&vs10)->QuerySignature2(guid);
		return vs10.QuerySignature2(guid);
	}
};

struct Src {
	virtual bool Close(void);
	virtual bool Add(struct SrcHeader const *,void const *);
	virtual bool Remove(char const *);
	virtual bool QueryByName(char const *,struct SrcHeaderOut *)const ;
	virtual bool GetData(struct SrcHeaderOut const *,void *)const ;
	virtual bool GetEnum(struct EnumSrc * *)const ;
	virtual bool GetHeaderBlock(struct SrcHeaderBlock &)const ;
	virtual bool RemoveW(unsigned short *);
	virtual bool QueryByNameW(unsigned short *,struct SrcHeaderOut *)const ;
	virtual bool AddW(struct SrcHeaderW const *,void const *);
};

#include "pshpack1.h"

struct LineInfoEntry
{
	unsigned int offset;
	unsigned short line;
};

struct LineInfo
{
	unsigned int cntEntries;
	unsigned short unknown;
	LineInfoEntry entries[1]; // first entry { 0, 0x7fff }
};

struct SymbolChunk
{
	unsigned int chunkType; // seen 0xf1 (symbols), f2(??) f3 (FPO), f4 (MD5?), f5 (NEWFPO)
	unsigned int chunkSize; // 0x18a: size of compiler symbols

	// symbol entries
	// S_COMPILER_V4
	// S_MSTOOL_V4
};

struct SymbolData
{
	unsigned int magic; // 4: version? sizeof header?
	// followed by SymbolChunks
};

struct TypeChunk
{
	// see also codeview_type

	unsigned short len;
	unsigned short type;

	/*union
	{*/
		struct _refpdb // type 0x1515
		{
			unsigned int md5[4];
			unsigned int unknown;
			unsigned pdbname[1];
		} refpdb;
	/*};*/
};

struct TypeData
{
	unsigned int magic; // 4: version? sizeof header?
	// followed by TypeChunks
};

#include "poppack.h"

struct Mod {
	virtual unsigned long QueryInterfaceVersion(void);
	virtual unsigned long QueryImplementationVersion(void);
	virtual int AddTypes(unsigned char *pTypeData,long cbTypeData);
	virtual int AddSymbols(unsigned char *pSymbolData,long cbSymbolData);
	virtual int AddPublic(char const *,unsigned short,long); // forwards to AddPublic2(...,0)
	virtual int AddLines(char const *fname,unsigned short sec,long off,long size,long off2,unsigned short firstline,unsigned char *pLineInfo,long cbLineInfo); // forwards to AddLinesW
	virtual int AddSecContrib(unsigned short sec,long off,long size,unsigned long secflags); // forwards to AddSecContribEx(..., 0, 0)
	virtual int QueryCBName(long *);
	virtual int QueryName(char * const,long *);
	virtual int QuerySymbols(unsigned char *,long *);
	virtual int QueryLines(unsigned char *,long *);
	virtual int SetPvClient(void *);
	virtual int GetPvClient(void * *);
	virtual int QueryFirstCodeSecContrib(unsigned short *,long *,long *,unsigned long *);
	virtual int QueryImod(unsigned short *);
	virtual int QueryDBI(struct DBI * *);
	virtual int Close(void);
	virtual int QueryCBFile(long *);
	virtual int QueryFile(char * const,long *);
	virtual int QueryTpi(struct TPI * *);
	virtual int AddSecContribEx(unsigned short sec,long off,long size,unsigned long secflags,unsigned long crc/*???*/,unsigned long);
	virtual int QueryItsm(unsigned short *);
	virtual int QuerySrcFile(char * const,long *);
	virtual int QuerySupportsEC(void);
	virtual int QueryPdbFile(char * const,long *);
	virtual int ReplaceLines(unsigned char *,long);
	virtual bool GetEnumLines(struct EnumLines * *);
	virtual bool QueryLineFlags(unsigned long *);
	virtual bool QueryFileNameInfo(unsigned long,unsigned short *,unsigned long *,unsigned long *,unsigned char *,unsigned long *);
	virtual int AddPublicW(unsigned short const *,unsigned short,long,unsigned long);
	virtual int AddLinesW(unsigned short const *fname,unsigned short sec,long off,long size,long off2,unsigned long firstline,unsigned char *plineInfo,long cbLineInfo);
	virtual int QueryNameW(unsigned short * const,long *);
	virtual int QueryFileW(unsigned short * const,long *);
	virtual int QuerySrcFileW(unsigned short * const,long *);
	virtual int QueryPdbFileW(unsigned short * const,long *);
	virtual int AddPublic2(char const *name,unsigned short sec,long off,unsigned long type);
	virtual int InsertLines(unsigned char *,long);
	virtual int QueryLines2(long,unsigned char *,long *);
};


struct DBI_part1 {
	virtual unsigned long QueryImplementationVersion(void);
	virtual unsigned long QueryInterfaceVersion(void);
	virtual int OpenMod(char const *objName,char const *libName,struct Mod * *);
	virtual int DeleteMod(char const *);
	virtual int QueryNextMod(struct Mod *,struct Mod * *);
	virtual int OpenGlobals(struct GSI * *);
	virtual int OpenPublics(struct GSI * *);
	virtual int AddSec(unsigned short sec,unsigned short flags,long offset,long cbseg);
	virtual int QueryModFromAddr(unsigned short,long,struct Mod * *,unsigned short *,long *,long *);
	virtual int QuerySecMap(unsigned char *,long *);
	virtual int QueryFileInfo(unsigned char *,long *);
	virtual void DumpMods(void);
	virtual void DumpSecContribs(void);
	virtual void DumpSecMap(void);
	virtual int Close(void);
	virtual int AddThunkMap(long *,unsigned int,long,struct SO *,unsigned int,unsigned short,long);
	virtual int AddPublic(char const *,unsigned short,long);
	virtual int getEnumContrib(struct Enum * *);
	virtual int QueryTypeServer(unsigned char,struct TPI * *);
	virtual int QueryItsmForTi(unsigned long,unsigned char *);
	virtual int QueryNextItsm(unsigned char,unsigned char *);
	virtual int reinitialize(void); // returns 0 (QueryLazyTypes in 10.0)
	virtual int SetLazyTypes(int);
	virtual int FindTypeServers(long *,char *);
	virtual void noop(void); // noop (_Reserved_was_QueryMreLog in 10.0)
	virtual int OpenDbg(enum DBGTYPE,struct Dbg * *);
	virtual int QueryDbgTypes(enum DBGTYPE *,long *);
	virtual int QueryAddrForSec(unsigned short *,long *,unsigned short,long,unsigned long,unsigned long);
};
struct DBI_part2 : public DBI_part1 {
// in mspdb100.dll:
	virtual int QueryAddrForSecEx(unsigned short *,long *,unsigned short,long,unsigned long,unsigned long);
};

template<typename BASE> 
struct DBI_BASE : public BASE {
	virtual int QuerySupportsEC(void);
	virtual int QueryPdb(struct PDB * *);
	virtual int AddLinkInfo(struct LinkInfo *);
	virtual int QueryLinkInfo(struct LinkInfo *,long *);
	virtual unsigned long QueryAge(void)const ;
	virtual int reinitialize2(void);  // returns 0 (QueryLazyTypes in 10.0)
	virtual void FlushTypeServers(void);
	virtual int QueryTypeServerByPdb(char const *,unsigned char *);
	virtual int OpenModW(unsigned short const *objName,unsigned short const *libName,struct Mod * *);
	virtual int DeleteModW(unsigned short const *);
	virtual int AddPublicW(unsigned short const *name,unsigned short sec,long off,unsigned long type);
	virtual int QueryTypeServerByPdbW(unsigned short const *,unsigned char *);
	virtual int AddLinkInfoW(struct LinkInfoW *);
	virtual int AddPublic2(char const *name,unsigned short sec,long off,unsigned long type);
	virtual unsigned short QueryMachineType(void)const ;
	virtual void SetMachineType(unsigned short);
	virtual void RemoveDataForRva(unsigned long,unsigned long);
	virtual int FStripped(void);
	virtual int QueryModFromAddr2(unsigned short,long,struct Mod * *,unsigned short *,long *,long *,unsigned long *);
	virtual int QueryNoOfMods(long *);
	virtual int QueryMods(struct Mod * *,long);
	virtual int QueryImodFromAddr(unsigned short,long,unsigned short *,unsigned short *,long *,long *,unsigned long *);
	virtual int OpenModFromImod(unsigned short,struct Mod * *);
	virtual int QueryHeader2(long,unsigned char *,long *);
	virtual int FAddSourceMappingItem(unsigned short const *,unsigned short const *,unsigned long);
	virtual int FSetPfnNotePdbUsed(void *,void (__cdecl*)(void *,unsigned short const *,int,int));
	virtual int FCTypes(void);
	virtual int QueryFileInfo2(unsigned char *,long *);
	virtual int FSetPfnQueryCallback(void *,int (__cdecl*(__cdecl*)(void *,enum DOVC))(void));
};

struct DBI_VS9  : public DBI_BASE<DBI_part1> {};
struct DBI_VS10 : public DBI_BASE<DBI_part2> {};

struct DBI
{
    DBI_VS9 vs9;

    unsigned long QueryImplementationVersion() { return vs9.QueryImplementationVersion(); }
    unsigned long QueryInterfaceVersion() { return vs9.QueryInterfaceVersion(); }
    int Close() { return vs9.Close(); }
    int OpenMod(char const *objName,char const *libName,struct Mod * *pmod) { return vs9.OpenMod(objName,libName,pmod); }
    int AddSec(unsigned short sec,unsigned short flags,long offset,long cbseg) { return vs9.AddSec(sec,flags,offset,cbseg); }

    int AddPublic2(char const *name,unsigned short sec,long off,unsigned long type)
    {
        if(vsVersion >= 10)
            return ((DBI_VS10*) &vs9)->AddPublic2(name, sec, off, type);
        return vs9.AddPublic2(name, sec, off, type);
    }
    void SetMachineType(unsigned short type)
    {
        if(vsVersion >= 10)
            return ((DBI_VS10*) &vs9)->SetMachineType(type);
        return vs9.SetMachineType(type);
    }
};

struct StreamCached {
	virtual long QueryCb(void);
	virtual int Read(long,void *,long *);
	virtual int Write(long,void *,long);
	virtual int Replace(void *,long);
	virtual int Append(void *,long);
	virtual int Delete(void);
	virtual int Release(void);
	virtual int Read2(long,void *,long);
	virtual int Truncate(long);
};

struct GSI {
	virtual unsigned long QueryInterfaceVersion(void);
	virtual unsigned long QueryImplementationVersion(void);
	virtual unsigned char * NextSym(unsigned char *);
	virtual unsigned char * HashSymW(unsigned short const *,unsigned char *);
	virtual unsigned char * NearestSym(unsigned short,long,long *);
	virtual int Close(void);
	virtual int getEnumThunk(unsigned short,long,struct EnumThunk * *);
	virtual int QueryTpi(struct TPI * *); // returns 0
	virtual int QueryTpi2(struct TPI * *); // returns 0
	virtual unsigned char * HashSymW2(unsigned short const *,unsigned char *); // same as HashSymW
	virtual int getEnumByAddr(struct EnumSyms * *);
};

struct TPI {
	virtual unsigned long QueryInterfaceVersion(void);
	virtual unsigned long QueryImplementationVersion(void);
	virtual int QueryTi16ForCVRecord(unsigned char *,unsigned short *);
	virtual int QueryCVRecordForTi16(unsigned short,unsigned char *,long *);
	virtual int QueryPbCVRecordForTi16(unsigned short,unsigned char * *);
	virtual unsigned short QueryTi16Min(void);
	virtual unsigned short QueryTi16Mac(void);
	virtual long QueryCb(void);
	virtual int Close(void);
	virtual int Commit(void);
	virtual int QueryTi16ForUDT(char const *,int,unsigned short *);
	virtual int SupportQueryTiForUDT(void);
	virtual int fIs16bitTypePool(void);
	virtual int QueryTiForUDT(char const *,int,unsigned long *);
	virtual int QueryTiForCVRecord(unsigned char *,unsigned long *);
	virtual int QueryCVRecordForTi(unsigned long,unsigned char *,long *);
	virtual int QueryPbCVRecordForTi(unsigned long,unsigned char * *);
	virtual unsigned long QueryTiMin(void);
	virtual unsigned long QueryTiMac(void);
	virtual int AreTypesEqual(unsigned long,unsigned long);
	virtual int IsTypeServed(unsigned long);
	virtual int QueryTiForUDTW(unsigned short const *,int,unsigned long *);
};


struct NameMap {
	virtual int close(void);
	virtual int reinitialize(void);
	virtual int getNi(char const *,unsigned long *);
	virtual int getName(unsigned long,char const * *);
	virtual int getEnumNameMap(struct Enum * *);
	virtual int contains(char const *,unsigned long *);
	virtual int commit(void);
	virtual int isValidNi(unsigned long);
	virtual int getNiW(unsigned short const *,unsigned long *);
	virtual int getNameW(unsigned long,unsigned short *,unsigned int *);
	virtual int containsW(unsigned short const *,unsigned long *);
	virtual int containsUTF8(char const *,unsigned long *);
	virtual int getNiUTF8(char const *,unsigned long *);
	virtual int getNameA(unsigned long,char const * *);
	virtual int getNameW2(unsigned long,unsigned short const * *);
};

struct EnumNameMap {
	virtual void release(void);
	virtual void reset(void);
	virtual int next(void);
	virtual void get(char const * *,unsigned long *);
};

struct EnumNameMap_Special {
	virtual void release(void);
	virtual void reset(void);
	virtual int next(void);
	virtual void get(char const * *,unsigned long *);
};

} // namespace mspdb

bool initMsPdb();
bool exitMsPdb();

mspdb::PDB* CreatePDB(const wchar_t* pdbname);

extern char* mspdb_dll;

#endif // __MSPDB_H__
