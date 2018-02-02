


#include "../base/types_utils.h"
#include <boost/date_time.hpp>
namespace bt = boost::posix_time;

SMILE_NS_BEGIN

/** VALUE PARSING FUNCTIONS **/

bool parseBool( const std::string& value ) {
  if(value == "false") return false;
  return true;
}

int32_t parseInt32( const std::string& value ) {
  std::size_t numread;
  const auto num = static_cast<int32_t>(std::stoi(value,&numread));
  if(numread != value.length()) {
    std::cerr << "WARNING: processing of value " << value << " was not correct :" << num << std::endl;
  }
  return num;
}

int64_t parseInt64( const std::string& value ){

  std::size_t numread;
  const auto num = static_cast<int64_t>(std::stol(value,&numread));
  if(numread != value.length()) {
    std::cerr << "WARNING: processing of value " << value << " was not correct :" << num << std::endl;
  }
  return num;
}

uint32_t parseUInt32( const std::string& value ) {
  std::size_t numread;
  const auto num = static_cast<uint32_t>(std::stoul(value,&numread));
  if(numread != value.length()) {
    std::cerr << "WARNING: processing of value " << value << " was not correct :" << num << std::endl;
  }
  return num;
}

uint64_t parseUInt64( const std::string& value ){ 
  std::size_t numread;
  const auto num = static_cast<uint64_t>(std::stoull(value,&numread));
  if(numread != value.length()) {
    std::cerr << "WARNING: processing of value " << value << " was not correct :" << num << std::endl;
  }
  return num;
}

float parseFloat(const std::string& value ){
  std::size_t numread;
  const auto num = static_cast<float>(std::stof(value,&numread));
  if(numread != value.length()) {
    std::cerr << "WARNING: processing of value " << value << " was not correct :" << num << std::endl;
  }
  return num;
}

double parseDouble(const std::string& value ){
  std::size_t numread;
  const auto num = static_cast<float>(std::stod(value,&numread));
  if(numread != value.length()) {
    std::cerr << "WARNING: processing of value " << value << " was not correct :" << num << std::endl;
  }
  return num;
}

std::locale locale(std::locale::classic(), new bt::time_input_facet("%Y-%m-%dT%H:%M:%S%F+0000"));
bt::ptime timet_start(boost::gregorian::date(1970,1,1));

timestamp parseTimestamp( const std::string& value ) {
  /*bt::ptime pt;
  std::istringstream is(value);
  is.imbue(locale);
  is >> pt;
  if(pt == bt::ptime()) std::cout << "WARNING: error parsing timestmap: " << value << " " << pt << std::endl;
  bt::time_duration diff = pt - timet_start;
  auto time =  static_cast<uint64_t>(diff.ticks()/bt::time_duration::rep_type::ticks_per_second);
  */
  return timestamp{0};
}

SMILE_NS_END

