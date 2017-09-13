//
// Created by Lei Pi on 2/24/17.
//

#include "FaceHolder.hpp"

namespace ndn {
namespace homesec {

shared_ptr<Face>
FaceHolder::get()
{
  static FaceHolder ins;
  return ins.m_face;
}

} // namespace homesec
} // namespace ndn
