

/**
*Just a lot of useful functions and classes taken from gpp library.
*This file is only for quick, one-off testing.
*Contains log functions, timestamps, profiling and other things.
*Written by Roger in oct 2023
*rogerlasch@gmail.com
**/

#ifndef GPP_UTILS_H
#define GPP_UTILS_H

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include<mutex>
#include<shared_mutex>
#include<atomic>
#include<thread>
#include<algorithm>
#include<functional>
#include<exception>
#include<chrono>
#include<codecvt>
#include<string.h>
#include<random>
#include<format>
#include<memory>
#include<string>
#include<iostream>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<sstream>
#include<fstream>
#include<vector>
#include<codecvt>
#include<stdint.h>

#pragma warning(disable: 4834)
namespace gpp{

typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;

//Time
inline int64 get_timestamp_sec();
inline int64 get_timestamp_ms();
inline int64 get_timestamp_mcs();
inline int64 get_timestamp_ns();
inline float gpp_nanoseconds_to_milliseconds(int64 ns);
inline void wait_ms(uint64 ms);
inline void wait_mcs(uint64 mcs);
inline void wait_ns(uint64 ns);
inline uint32 random_uint32(uint32 rMin, uint32 rMax);
inline uint64 random_uint64(uint64 rMin, uint64 rMax);
inline float random_float(float rmin, float rmax);

//String

inline std::string string_to_lower_case(const std::string& s);
inline std::wstring wstring_to_lower_case(const std::wstring& s);
inline void string_to_lower_case(std::string& s);
inline void wstring_to_lower_case(std::wstring& s);
inline std::string string_to_upper_case(const std::string& s);
inline std::wstring wstring_to_upper_case(const std::wstring& s);
inline void string_to_upper_case(std::string& s);
inline void wstring_to_upper_case(std::wstring& s);
inline std::string string_trim(const std::string& s);
inline std::wstring wstring_trim(const std::wstring& s);
inline void string_trim(std::string& s);
inline void wstring_trim(std::wstring& s);
inline std::string string_replace(const std::string& str, const std::string& old, const std::string& new_str);
inline std::string string_replace(const std::string& str, const std::vector<std::pair<std::string, std::string>>& args);
inline std::wstring wstring_replace(const std::wstring& str, const std::wstring& old, const std::wstring& new_str);
inline std::wstring wstring_replace(const std::wstring& str, const std::vector<std::pair<std::wstring, std::wstring>>& args);
inline std::string string_utf8_encode(const std::wstring& str);
inline std::wstring string_utf8_decode(const std::string& str);
inline std::string wstring_to_string(const std::wstring& str);
inline std::wstring string_to_wstring(const std::string& str);
inline uint32 string_split(const std::string& str, const std::string& delin, std::vector<std::string>& out);
inline uint32 string_split(const std::wstring& str, const std::wstring& delin, std::vector<std::wstring>& out);

//Log and depuration...

enum gpp_value_types
{
gpp_type_void=0,
gpp_type_int8,
gpp_type_uint8,
gpp_type_int16,
gpp_type_uint16,
gpp_type_int32,
gpp_type_uint32,
gpp_type_int64,
gpp_type_uint64,
gpp_type_string,
gpp_type_wstring,
gpp_type_float,
gpp_type_double,
gpp_type_bool
};


class gpp_value
{
private:
union
{
bool bool_;
int64 int64_;
uint64 uint64_;
double double_;
std::string* string_;
} storage;
uint32 type;
public:
inline gpp_value();
inline gpp_value(const gpp_value& val);
inline gpp_value(int8 val);
inline gpp_value(uint8 val);
inline gpp_value(int16 val);
inline gpp_value(uint16 val);
inline gpp_value(int32 val);
inline gpp_value(uint32 val);
inline gpp_value(int64 val);
inline gpp_value(uint64 val);
inline gpp_value(float val);
inline gpp_value(double val);
inline gpp_value(bool val);
inline gpp_value(const std::string& s);
inline gpp_value& operator=(const gpp_value& val);
inline uint32 gettype()const;
inline void cleanup();
inline ~gpp_value();
inline std::string toString()const;
inline bool get(int8& val)const;
inline bool get(uint8& val)const;
inline bool get(int16& val)const;
inline bool get(uint16& val)const;
inline bool get(int32& val)const;
inline bool get(uint32& val)const;
inline bool get(int64& val)const;
inline bool get(uint64& val)const;
inline bool get(float& val)const;
inline bool get(double& val)const;
inline bool get(bool& val)const;
inline bool get(std::string& val)const;
};

inline std::ostream& operator<<(std::ostream& os, gpp::gpp_value& val);

typedef std::vector<gpp::gpp_value> gpp_value_args;

template<class ...Args>
inline gpp_value_args gpp_make_args(const Args&... args)
{
gpp_value_args vect={args...};
return vect;
}

class gpp_exception : public std::exception
{
private:
std::string msg;
public:
inline gpp_exception(const std::string& msg);
inline gpp_exception(const std::string& msg, const std::string& function_name, const std::string& filename, int line);
inline gpp_exception(const gpp_exception& gx);
inline gpp_exception& operator=(const gpp_exception& gx);
inline virtual ~gpp_exception();
inline virtual const char* what() const noexcept override;
};
#define _GEXCEPT(msg) gpp_exception(msg, __FUNCTION__, __FILE__, __LINE__)

class logger
{
public:
int32 level;
uint32 flags;
std::string filename;
std::vector<std::string> stacktrace;
std::ofstream ofn;
inline logger(const std::string& filename, int32 level);
logger(const logger& lg)=delete;
logger& operator=(const logger& lg)=delete;
inline virtual ~logger();
};

enum GPP_LOG_LEVEL
{
LG_ALL=0,
LG_DEBUG,
LG_BACKTRACE,
LG_ERROR,
LG_WARNING,
LG_INFO,
LG_CRITICAL
};


enum GPP_LOGGER_FLAGS
{
GLOG_CONSOLE=1
};

inline bool log_create(const std::string& filename, int32 level);
inline void log_close(const std::string& filename);
inline bool log_set_level(const std::string& filename, int32 level);
inline bool log_setopt(const std::string& filename, uint32 opt, bool enable);
inline bool log_getopt(const std::string& filename, uint32 opt);
inline bool log_set_default(const std::string& filename);
inline void log_write(const std::string& filename, int32 level, const std::string& str);
inline void log_start_backtrace(const std::string& filename);
inline void log_dump_backtrace(const std::string& filename);

template<class ...Args>
inline std::string safe_format(const std::string& str, const Args& ...args)
{
std::string final="";
try {
final=std::vformat(str, std::make_format_args(args...));
} catch(const std::exception& e) {
e.what();
return "";
}
return final;
}

template<class ...Args>
inline std::wstring safe_wformat(const std::wstring& str, const Args& ...args)
{
std::wstring final=L"";
try {
final=std::vformat(str, std::make_wformat_args(args...));
} catch(const std::exception& e) {
e.what();
return L"";
}
return final;
}

#define _GDEBUG(str, ...) log_write("", LG_DEBUG, safe_format(str, __VA_ARGS__))
#define _GBACKTRACE(str, ...) log_write("", LG_BACKTRACE, safe_format(str, __VA_ARGS__))
#define _GERROR(str, ...) log_write("", LG_ERROR, safe_format(str, __VA_ARGS__))
#define _GWARNING(str, ...) log_write("", LG_WARNING, safe_format(str, __VA_ARGS__))
#define _GINFO(str, ...) log_write("", LG_INFO, safe_format(str, __VA_ARGS__))
#define _GCRITICAL(str, ...) log_write("", LG_CRITICAL, safe_format(str, __VA_ARGS__))

#undef _GASSERT
#undef _GASSERT_MSG
#define _GASSERT(expr)\
if(!(expr)) {\
log_write("", LG_CRITICAL, safe_format("Assertion error in file: {}, Line: {}, Expression: \"{}\"", __FILE__, __LINE__, #expr));\
std::terminate();\
}
//End macro

#define _GASSERT_MSG(expr, str, ...)\
if(!(expr)) {\
log_write("", LG_CRITICAL, safe_format("Assertion error in file: {}, Line: {}, Expression: \"{}\"\nMsg: {}", __FILE__, __LINE__, #expr, safe_format(str, __VA_ARGS__)));\
std::terminate();\
}
//End macro...

class FunctionInfo
{
public:
std::atomic<int64> total_time;
std::atomic<int64> total_executions;
std::string func_name;
inline FunctionInfo();
FunctionInfo(const FunctionInfo& f)=delete;
FunctionInfo& operator=(const FunctionInfo& f)=delete;
inline std::string toString();
};
typedef std::shared_ptr<FunctionInfo> functioninfo_ptr;

class ProfilerSnap
{
private:
int64 start_time;
std::string func_name;
public:
inline ProfilerSnap(const std::string& func_name);
ProfilerSnap(const ProfilerSnap& ps)=delete;
ProfilerSnap& operator=(const ProfilerSnap& ps)=delete;
inline virtual ~ProfilerSnap();
};

class ProfilerTable
{
public:
std::vector<std::vector<std::string>> htable;
inline ProfilerTable();
ProfilerTable(const ProfilerTable& pf)=delete;
ProfilerTable& operator=(const ProfilerTable& t)=delete;
inline void appendHeader(const std::vector<std::string>& h);
inline void addRow(const std::vector<gpp_value>& row);
inline std::string toString();
};
typedef std::shared_ptr<ProfilerTable> profiler_table_ptr;

inline void profiler_start();
inline void profiler_dump(const std::string& filename);
inline void profiler_log_snap(const std::string& func_name, int64 execution_time_ns);
inline void profiler_set_int(const std::string& vname, int64 value);
inline int64 profiler_get_int(const std::string& vname);
inline void profiler_inc(const std::string& vname, int64 qtd);
inline void profiler_dec(const std::string& vname, int64 qtd);
inline void profiler_set_value(const std::string& var_name, const gpp_value& val);
inline gpp_value profiler_get_value(const std::string& var_name);
inline void profiler_create_table(const std::string& tname, const std::vector<std::string> header);
inline void profiler_add_row(const std::string& tname, const std::vector<gpp_value>& values);
#define profiler_snap() ProfilerSnap PROFILER_SNAP_INFO_DATA(__FUNCTION__)

#define G_FILENAME "log_main.txt"
class gpp_starter{
public:
inline gpp_starter(){
std::setlocale(LC_ALL, "Portuguese");
std::cout<<std::fixed;
std::cout.precision(2);
log_create(G_FILENAME, LG_ALL);
log_set_default(G_FILENAME);
profiler_start();
}
inline ~gpp_starter(){
profiler_dump("profiler_main.txt");
}
};

}
#endif

#ifndef GPP_UTILS_IMPLEMENTATION_CPP
#define GPP_UTILS_IMPLEMENTATION_CPP

namespace gpp{
using namespace std;
int64 get_timestamp_sec()
{
chrono::system_clock::time_point tp=chrono::system_clock::now();
chrono::system_clock::duration dtn=tp.time_since_epoch();
return chrono::duration_cast<chrono::seconds>(dtn).count();
}

int64 get_timestamp_ms()
{
chrono::system_clock::time_point tp=chrono::system_clock::now();
chrono::system_clock::duration dtn=tp.time_since_epoch();
return chrono::duration_cast<chrono::milliseconds>(dtn).count();
}

float gpp_nanoseconds_to_milliseconds(int64 ns)
{
return 0;
}
int64 get_timestamp_mcs()
{
chrono::system_clock::time_point tp=chrono::system_clock::now();
chrono::system_clock::duration dtn=tp.time_since_epoch();
return chrono::duration_cast<chrono::microseconds>(dtn).count();
}

int64 get_timestamp_ns()
{
chrono::system_clock::time_point tp=chrono::system_clock::now();
chrono::system_clock::duration dtn=tp.time_since_epoch();
return chrono::duration_cast<chrono::nanoseconds>(dtn).count();
}

void wait_ms(uint64 ms)
{
this_thread::sleep_for(chrono::milliseconds(ms));
}

void wait_mcs(uint64 mcs)
{
this_thread::sleep_for(chrono::microseconds(mcs));
}

void wait_ns(uint64 ns)
{
this_thread::sleep_for(chrono::nanoseconds(ns));
}

uint32 random_uint32(uint32 rMin, uint32 rMax)
{
static mt19937 rd(static_cast<uint32>(get_timestamp_ms()));
static uniform_int_distribution<> distribution(rMin, rMax);
return distribution(rd);
}

uint64 random_uint64(uint64 rMin, uint64 rMax)
{
static mt19937_64 rd(static_cast<uint32>(get_timestamp_ms()));
static uniform_int_distribution<> distribution(rMin, rMax);
return distribution(rd);
}

float random_float(float rmin, float rmax)
{
random_device randdev;
mt19937 generator(randdev());
uniform_real_distribution<> distrib(rmin, rmax);
return static_cast<float>(distrib(generator));
}

string string_to_lower_case(const string& s)
{
string final="";
final.reserve(s.size());
for(uint32 i=0; i<s.size(); i++)
{
final+=tolower(s[i]);
}
return final;
}

wstring wstring_to_lower_case(const wstring& s)
{
wstring final=L"";
final.reserve(s.size());
for(uint32 i=0; i<s.size(); i++)
{
final+=tolower(s[i]);
}
return final;
}

void string_to_lower_case(string& s)
{
for(uint32 i=0; i<s.size(); i++)
{
s[i]=tolower(s[i]);
}
}

void wstring_to_lower_case(wstring& s)
{
for(uint32 i=0; i<s.size(); i++)
{
s[i]=tolower(s[i]);
}
}

string string_to_upper_case(const string& s)
{
string final="";
final.reserve(s.size());
for(uint32 i=0; i<s.size(); i++)
{
final+=toupper(s[i]);
}
return final;
}

wstring wstring_to_upper_case(const wstring& s)
{
wstring final=L"";
final.reserve(s.size());
for(uint32 i=0; i<s.size(); i++)
{
final+=toupper(s[i]);
}
return final;
}

void string_to_upper_case(string& s)
{
for(uint32 i=0; i<s.size(); i++)
{
s[i]=toupper(s[i]);
}
}

void wstring_to_upper_case(wstring& s)
{
for(uint32 i=0; i<s.size(); i++)
{
s[i]=toupper(s[i]);
}
}

string string_trim(const string& s)
{
static string t = " \t\r\n";
string d = s;
string::size_type i = d.find_last_not_of(t);
if(i ==std::string::npos)
{
         return "";
}
      else
{
         return d.erase(i + 1).erase(0, s.find_first_not_of(t));
}
}

wstring wstring_trim(const wstring& s)
{
static wstring t =L" \t\r\n";
wstring d = s;
wstring::size_type i = d.find_last_not_of(t);
if(i ==std::wstring::npos)
{
         return L"";
}
      else
{
         return d.erase(i + 1).erase(0, s.find_first_not_of(t));
}
}

void string_trim(string& s)
{
static string t = " \t\r\n";
string::size_type i=s.find_last_not_of(t);
if(i ==std::string::npos)
{
return;
}
      else
{
s.erase(i + 1).erase(0, s.find_first_not_of(t));
}
}

void wstring_trim(wstring& s)
{
static wstring t = L" \t\r\n";
wstring::size_type i=s.find_last_not_of(t);
if(i ==std::wstring::npos)
{
return;
}
      else
{
s.erase(i + 1).erase(0, s.find_first_not_of(t));
}
}

string string_replace(const string& str, const string& old, const string& new_str)
{
string mstr(str);
size_t x=0;
while((x=mstr.find(old, x))!=string::npos)
{
mstr.replace(x, old.size(), new_str);
}
return mstr;
}

string string_replace(const string& str, const vector<pair<string, string>>& args)
{
string mstr(str);
for(auto& it : args)
{
size_t x=0;
while((x=mstr.find(it.first, x))!=string::npos)
{
mstr.replace(x, it.first.size(), it.second);
}
}
return mstr;
}

wstring wstring_replace(const wstring& str, const wstring& old, const wstring& new_str)
{
wstring mstr(str);
size_t x=0;
while((x=mstr.find(old, x))!=wstring::npos)
{
mstr.replace(x, old.size(), new_str);
}
return mstr;
}

wstring wstring_replace(const wstring& str, const vector<pair<wstring, wstring>>& args)
{
wstring mstr(str);
for(auto& it : args)
{
size_t x=0;
while((x=mstr.find(it.first, x))!=wstring::npos)
{
mstr.replace(x, it.first.size(), it.second);
}
}
return mstr;
}

//Conversions...

string string_utf8_encode(const wstring& str)
{
try {
    wstring_convert<codecvt_utf8_utf16<wchar_t>> myconv;
    return myconv.to_bytes(str);
} catch(const exception& e) {
_GEXCEPT(e.what());
}
return "";
}

wstring string_utf8_decode(const string& str)
{
try {
wstring_convert<codecvt_utf8_utf16<wchar_t>> myconv;
    return myconv.from_bytes(str);
} catch(const exception& e) {
_GEXCEPT(e.what());
}
return L"";
}

string wstring_to_string(const wstring& str)
{
locale loc;
const auto& _Facet=use_facet<codecvt<char, wchar_t, mbstate_t>>(loc);
string final="";
final.resize(str.size());
mbstate_t _State{};
const wchar_t* istart=str.c_str();
const wchar_t* iend=(str.c_str()+str.size());
const wchar_t* inext=NULL;
char* ostart=(char*)final.c_str();
char* oend=(char*)(final.c_str()+final.size());
char* onext=NULL;
const auto Result=_Facet.in(_State, istart, iend, inext, ostart, oend, onext);
if(Result==codecvt_base::ok)
{
final.resize(static_cast<size_t>(onext-ostart));
return final;
}
return "";
}

wstring string_to_wstring(const string& str)
{
locale loc;
const auto& _Facet=use_facet<codecvt<wchar_t, char, mbstate_t>>(loc);
wstring final=L"";
final.resize(str.size());
mbstate_t _State{};
const char* istart=str.c_str();
const char* iend=(str.c_str()+str.size());
const char* inext=NULL;
wchar_t* ostart=(wchar_t*)final.c_str();
wchar_t* oend=(wchar_t*)(final.c_str()+final.size());
wchar_t* onext=NULL;
const auto Result=_Facet.in(_State, istart, iend, inext, ostart, oend, onext);
if(Result==codecvt_base::ok)
{
final.resize(static_cast<size_t>(onext-ostart));
return final;
}
return L"";
}

uint32 string_split(const std::string& str, const std::string& delin, std::vector<std::string>& out) {
    out.clear();
    size_t start = 0;
    size_t end = str.find(delin);
    while (end != std::string::npos) {
        out.push_back(str.substr(start, end - start));
        start = end + delin.length();
        end = str.find(delin, start);
    }
    out.push_back(str.substr(start));
return out.size();
}

uint32 string_split(const std::wstring& str, const std::wstring& delin, std::vector<std::wstring>& out) {
    out.clear();
    size_t start = 0;
    size_t end = str.find(delin);
    while (end != std::wstring::npos) {
        out.push_back(str.substr(start, end - start));
        start = end + delin.length();
        end = str.find(delin, start);
    }
    out.push_back(str.substr(start));
return out.size();
}

gpp_value::gpp_value()
{
type=gpp_type_void;
memset(&storage, 0, sizeof(storage));
}

gpp_value::gpp_value(const gpp_value& val)
{
*this=val;
}

gpp_value::gpp_value(int8 val)
{
type=gpp_type_int8;
storage.int64_=val;
}

gpp_value::gpp_value(uint8 val)
{
type=gpp_type_uint8;
storage.uint64_=val;
}

gpp_value::gpp_value(int16 val)
{
type=gpp_type_int16;
storage.int64_=val;
}

gpp_value::gpp_value(uint16 val)
{
type=gpp_type_uint16;
storage.uint64_=val;
}

gpp_value::gpp_value(int32 val)
{
type=gpp_type_int32;
storage.int64_=val;
}

gpp_value::gpp_value(uint32 val)
{
type=gpp_type_uint32;
storage.uint64_=val;
}

gpp_value::gpp_value(int64 val)
{
type=gpp_type_int64;
storage.int64_=val;
}

gpp_value::gpp_value(uint64 val)
{
type=gpp_type_uint64;
storage.uint64_=val;
}

gpp_value::gpp_value(float val)
{
type=gpp_type_float;
storage.double_=val;
}

gpp_value::gpp_value(double val)
{
type=gpp_type_double;
storage.double_=val;
}

gpp_value::gpp_value(bool val)
{
type=gpp_type_bool;
storage.bool_=val;
}

gpp_value::gpp_value(const string& s)
{
type=gpp_type_string;
storage.string_=new string(s);
}

gpp_value& gpp_value::operator=(const gpp_value& val)
{
this->cleanup();
this->type=val.type;
switch(type)
{
case gpp_type_string:
{
storage.string_=new string(*val.storage.string_);
break;
}
default:
{
memcpy(&storage, &val.storage, sizeof(val.storage));
break;
}
}
return *this;
}

gpp_value::~gpp_value()
{
switch(type)
{
case gpp_type_string:
{
delete storage.string_;
memset(&storage, 0, sizeof(storage));
break;
}
default:
{
memset(&storage, 0, sizeof(storage));
}
}
}

uint32 gpp_value::gettype()const
{
return type;
}

void gpp_value::cleanup()
{
switch(type)
{
case gpp_type_string:
{
delete storage.string_;
memset(&storage, 0, sizeof(storage));
break;
}
default:
{
memset(&storage, 0, sizeof(storage));
}
}
type=gpp_type_void;
}

string gpp_value::toString()const
{
switch(type)
{
case gpp_type_string:
{
return *storage.string_;
}
case gpp_type_bool:
{
return ((storage.bool_==true) ? "true" : "false");
}
case gpp_type_int8:
case gpp_type_int16:
case gpp_type_int32:
case gpp_type_int64:
{
return std::to_string(storage.int64_);
}
case gpp_type_uint8:
case gpp_type_uint16:
case gpp_type_uint32:
case gpp_type_uint64:
{
return std::to_string(storage.uint64_);
}
case gpp_type_float:
case gpp_type_double:
{
return std::to_string(storage.double_);
}
default:
{
return "void";
}
}
}

bool gpp_value::get( int8& value)const
{
if(type!=gpp_type_int8)
{
return false;
}
value=static_cast<int8>(storage.int64_);
return true;
}

bool gpp_value::get( uint8& value)const
{
if(type!=gpp_type_uint8)
{
return false;
}
value=static_cast<uint8>(storage.uint64_);
return true;
}

bool gpp_value::get( int16& value)const
{
if(type!=gpp_type_int16)
{
return false;
}
value=static_cast<int16>(storage.int64_);
return true;
}

bool gpp_value::get( uint16& value)const
{
if(type!=gpp_type_uint16)
{
return false;
}
value=static_cast<uint16>(storage.uint64_);
return true;
}

bool gpp_value::get( int32& value)const
{
if(type!=gpp_type_int32)
{
return false;
}
value=static_cast<int32>(storage.int64_);
return true;
}

bool gpp_value::get( uint32& value)const
{
if(type!=gpp_type_uint32)
{
return false;
}
value=static_cast<uint32>(storage.uint64_);
return true;
}

bool gpp_value::get( int64& value)const
{
if(type!=gpp_type_int64)
{
return false;
}
value=storage.int64_;
return true;
}

bool gpp_value::get( uint64& value)const
{
if(type!=gpp_type_uint64)
{
return false;
}
value=storage.uint64_;
return true;
}

bool gpp_value::get( float& value)const
{
if(type!=gpp_type_float)
{
return false;
}
value=static_cast<float>(storage.double_);
return true;
}

bool gpp_value::get( double& value)const
{
if(type!=gpp_type_double)
{
return false;
}
value=storage.double_;
return true;
}

bool gpp_value::get( bool& value)const
{
if(type!=gpp_type_bool)
{
return false;
}
value=storage.bool_;
return true;
}

bool gpp_value::get( string& value)const
{
if(type!=gpp_type_string)
{
return false;
}
value=*storage.string_;
return true;
}

ostream& operator<<(ostream& os, gpp_value& val)
{
os<<val.toString();
return os;
}

gpp_exception::gpp_exception(const string& msg)
{
this->msg=msg;
}

gpp_exception::gpp_exception(const string& msg, const string& function_name, const string& filename, int line)
{
stringstream ss;
ss<<"Excessão gerada na função "<<function_name<<". Arquivo: "<<filename<<", Linha: "<<line<<endl<<"Descrição: "<<msg<<endl;
this->msg=ss.str();
}

gpp_exception::gpp_exception(const gpp_exception& gx)
{
*this=gx;
}

gpp_exception& gpp_exception::operator=(const gpp_exception& gx)
{
this->msg=gx.msg;
return *this;
}

gpp_exception::~gpp_exception()
{
}

const char * gpp_exception::what ( ) const throw ( )
{
return msg.c_str();
}

logger::logger(const string& filename, int level)
{
ofn.open(filename);
if(!ofn.is_open())
{
_GEXCEPT("Erro ao abrir o arquivo: "+filename);
}
this->filename=filename;
this->level=level;
this->flags=0;
stacktrace.clear();
}

logger::~logger()
{
ofn.close();
this->filename=filename;
this->level=level;
stacktrace.clear();
}

typedef shared_ptr<logger> shared_logger;
static unordered_map<string, shared_logger> logs;
static shared_logger default_log;

static mutex mtx_log;

static shared_logger get_log(const string& filename)
{
lock_guard<mutex> lck(mtx_log);
auto it=logs.find(filename);
return ((it==logs.end()) ? shared_logger() : it->second);
}

bool log_create(const string& filename, int32 level)
{
try {
lock_guard<mutex> lck(mtx_log);
if((filename.size()==0)||(logs.find(filename)!=logs.end()))
{
return false;
}
shared_logger lg=make_shared<logger>(filename, level);
logs.insert(make_pair(filename, lg));
} catch(const exception& e) {
return false;
}
return true;
}

void log_close(const string& filename)
{
lock_guard<mutex> lck(mtx_log);
auto it=logs.find(filename);
if(it!=logs.end())
{
logs.erase(it);
}
}

bool log_set_level(const string& filename, int32 level)
{
shared_logger log=get_log(filename);
if(log!=NULL)
{
log->level=level;
return true;
}
return false;
}

bool log_setopt(const string& filename, uint32 opt, bool enable)
{
shared_logger lg=get_log(filename);
if(lg==NULL)
{
return false;
}
if(enable)
{
if((lg->flags&opt)==0)
{
lg->flags|=opt;
return true;
}
}
else
{
if((lg->flags&opt)==opt)
{
lg->flags^=opt;
return true;
}
}
return true;
}

bool log_getopt(const string& filename, uint32 opt)
{
shared_logger lg=get_log(filename);
if(lg==NULL)
{
return false;
}
return (lg->flags&opt)==opt;
}

bool  log_set_default(const string& filename)
{
if(filename.size()==0)
{
default_log=shared_logger();
return true;
}
shared_logger lg=get_log(filename);
if(lg==NULL)
{
return false;
}
default_log=lg;
return true;
}

void log_write(const string& filename, int32 level, const string& str)
{
static unordered_map<int, string> lg_table={
{LG_ALL, ""},
{LG_DEBUG, "Debug"},
{LG_BACKTRACE, "BackTrace"},
{LG_ERROR, "Error"},
{LG_WARNING, "Warning"},
{LG_INFO, "Info"},
{LG_CRITICAL, "Falha Crítica"}
};
shared_logger lg=((filename.size()>0) ? get_log(filename) : default_log);
if(lg!=NULL)
{
if(level<lg->level)
{
return;
}
string tname=lg_table.at(level);
if(tname.size()==0) tname="Unknown";
string final=safe_format("{}: {}", tname, str);
switch(level)
{
case LG_BACKTRACE:
{
lg->stacktrace.emplace_back(final);
break;
}
default:
{
lg->ofn<<final<<endl;
if((lg->flags&GLOG_CONSOLE)==GLOG_CONSOLE)
{
cout<<final<<endl;
}
break;
}
}
}
}

void log_start_backtrace(const string& filename)
{
shared_logger log=get_log(filename);
if(log!=NULL)
{
log->stacktrace.clear();
log->stacktrace.emplace_back("Starting BackTrace...");
}
}

void log_dump_backtrace(const string& filename)
{
shared_logger log=get_log(filename);
if(log!=NULL)
{
if(log->stacktrace.size()>1)
{
log->stacktrace.emplace_back("End BackTrace...");
for(auto& row : log->stacktrace)
{
log->ofn<<row<<endl;
}
log->stacktrace.resize(0);
}
}
}

FunctionInfo::FunctionInfo()
{
func_name="";
total_executions.store(0);
total_time.store(0);
}

string FunctionInfo::toString()
{
stringstream ss;
ss<<fixed;
ss.precision(3);
float ftime=static_cast<float>(total_time.load())/1000000;
float average_time=(ftime/(float)total_executions.load());
ss<<func_name<<": Tempo total: "<<ftime<<" ms, Total de execuções: "<<total_executions.load();
if(average_time!=0.0f)
{
ss<<", Duração média: "<<average_time<<" ms"<<endl;
}
ss<<endl;
return ss.str();
}

ProfilerSnap::ProfilerSnap(const string& func_name)
{
this->func_name=func_name;
start_time=get_timestamp_ns();
}

ProfilerSnap::~ProfilerSnap()
{
int64 end_time=get_timestamp_ns();
int64 final_time=(end_time-start_time);
profiler_log_snap(func_name, final_time);
}

ProfilerTable::ProfilerTable()
{
htable.clear();
}

void ProfilerTable::appendHeader(const vector<string>& h)
{
if((h.size()==0)||(htable.size()>1))
{
return;
}
htable.resize(1);
htable[0]=h;
}

void ProfilerTable::addRow(const vector<gpp_value>& row)
{
if(htable.size()==0)
{
return;
}
vector<string> rw;
for(auto& it : row)
{
rw.push_back(it.toString());
}
if(rw.size()>htable[0].size()) rw.resize(htable[0].size());
if(rw.size()<htable[0].size()) rw.resize(htable[0].size(), "NULL");
htable.push_back(rw);
}

string ProfilerTable::toString()
{
stringstream ss;
for(auto& it : htable)
{
for(auto& it2 : it)
{
ss<<it2<<'\t';
}
ss<<endl;
}
return ss.str();
}

static int64 start_time=0;
static unordered_map<string, functioninfo_ptr> fn_table;
static unordered_map<string, int64> counter_table;
static unordered_map<string, gpp_value> v_table;
static unordered_map<string, profiler_table_ptr> htables;

void profiler_start()
{
if(start_time==0)
{
start_time=get_timestamp_ms();
fn_table.clear();
counter_table.clear();
v_table.clear();
htables.clear();
}
}

void profiler_dump(const string& filename)
{
stringstream ss;
if(start_time==0)
{
return;
}
string fname=((filename.size()==0) ? "gpp_profiler.txt" : filename);
ss<<"Tempo de execução total: "<<(get_timestamp_ms()-start_time)<<" ms"<<endl;
ss<<endl<<"Imprimindo funções monitoradas:"<<endl;
ss<<"Total de funções monitoradas: "<<fn_table.size()<<endl<<endl;
for(auto it=fn_table.begin(); it!=fn_table.end(); ++it)
{
ss<<it->second->toString();
}
if(counter_table.size()>0)
{
ss<<endl<<"Imprimindo variáveis de contagem..."<<endl;
ss<<"Total de variáveis a imprimir: "<<counter_table.size()<<endl<<endl;
for(auto it=counter_table.begin(); it!=counter_table.end(); ++it)
{
ss<<it->first<<": "<<it->second<<endl;
}
}
if(v_table.size()>0)
{
ss<<endl<<"Imprimindo variáveis gerais..."<<endl;
ss<<"Total de variáveis a imprimir: "<<v_table.size()<<endl<<endl;
for(auto it=v_table.begin(); it!=v_table.end(); ++it)
{
ss<<it->first<<": "<<it->second.toString()<<endl;
}
}
if(htables.size()>0)
{
ss<<"Imprimindo tabelas..."<<endl;
ss<<"Total de tabelas a imprimir: "<<htables.size()<<endl<<endl;
for(auto it=htables.begin(); it!=htables.end(); ++it)
{
ss<<it->second->toString()<<endl;
}
}
ofstream ofn(fname);
ofn<<fixed;
ofn.precision(2);
ofn<<ss.str();
ofn.close();
}

void profiler_log_snap(const string& func_name, int64 execution_time_ns)
{
auto it=fn_table.find(func_name);
if(it==fn_table.end())
{
functioninfo_ptr fn=make_shared<FunctionInfo>();
fn->func_name=func_name;
fn->total_time.fetch_add(execution_time_ns);
fn->total_executions.fetch_add(1);
fn_table.insert(make_pair(func_name, fn));
}
else
{
it->second->total_time.fetch_add(execution_time_ns);
it->second->total_executions.fetch_add(1);
}
}

void profiler_set_int(const string& vname, int64 value)
{
auto it=counter_table.find(vname);
if(it==counter_table.end())
{
counter_table.insert(make_pair(vname, value));
}
else
{
it->second=value;
}
}

int64 profiler_get_int(const string& vname)
{
auto it=counter_table.find(vname);
return ((it==counter_table.end()) ? 0 : it->second);
}

void profiler_inc(const string& vname, int64 qtd)
{
auto it=counter_table.find(vname);
if(it==counter_table.end())
{
profiler_set_int(vname, qtd);
}
else
{
it->second+=qtd;
}
}

void profiler_dec(const string& vname, int64 qtd)
{
auto it=counter_table.find(vname);
if(it==counter_table.end())
{
profiler_set_int(vname, qtd);
}
else
{
it->second-=qtd;
}
}

void profiler_set_value(const string& var_name, const gpp_value& val)
{
auto it=v_table.find(var_name);
if(it==v_table.end())
{
v_table.insert(make_pair(var_name, val));
}
else
{
it->second=val;
}
}

gpp_value profiler_get_value(const string& var_name)
{
auto it=v_table.find(var_name);
return ((it==v_table.end()) ? gpp_value() : it->second);
}

void profiler_create_table(const string& tname, const vector<string> header)
{
auto it=htables.find(tname);
if((it==htables.end())&&(tname.size()>0)&&(header.size()>0))
{
shared_ptr<ProfilerTable> hs=make_shared<ProfilerTable>();
hs->appendHeader(header);
htables.insert(make_pair(tname, hs));
}
}

void profiler_add_row(const string& tname, const vector<gpp_value>& values)
{
auto it=htables.find(tname);
if(it!=htables.end())
{
it->second->addRow(values);
}
}
}
#endif
using namespace gpp;
