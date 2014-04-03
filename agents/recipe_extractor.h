#ifndef RECIPE_EXTRACTOR_H_
#define RECIPE_EXTRACTOR_H_

#include <string>
#include "cyclus.h"

class RecipeExtractor : public cyclus::Facility {
 public:
  RecipeExtractor(cyclus::Context* ctx);
  virtual ~RecipeExtractor() {};
  virtual std::string str() {};

  virtual void DoRegistration();

  #pragma cyclus

  virtual void Tick(int time);
  virtual void Tock(int time) {};

 private:
  #pragma cyclus var {}
  std::string incommod_;
  #pragma cyclus var {}
  std::string wastecommod_;
  #pragma cyclus var {}
  std::string outcommod_;
  #pragma cyclus var {}
  std::string outrecipe_;
  #pragma cyclus var {}
  double inbuf_size_;
  #pragma cyclus var {}
  double outbuf_size_;
  #pragma cyclus var {}
  double wastebuf_size_;
  #pragma cyclus var {}
  double throughput_;
  #pragma cyclus var {'capacity': 'inbuf_size_'}
  cyclus::ResourceBuff inbuf_;
  #pragma cyclus var {'capacity': 'outbuf_size_'}
  cyclus::ResourceBuff outbuf_;
  #pragma cyclus var {'capacity': 'wastebuf_size_'}
  cyclus::ResourceBuff wastebuf_;

  SellPolicy outpolicy_;
  SellPolicy wastepolicy_;
  BuyPolicy inpolicy_;
};

#endif  // RECIPE_EXTRACTOR_H_
