//
// Created by Lei Pi on 2/24/17.
//

#ifndef HOMESEC_FACEHOLDER_HPP
#define HOMESEC_FACEHOLDER_HPP

#include <ndn-cxx/face.hpp>
#include <ndn-cxx/transport/tcp-transport.hpp>

namespace ndn {
namespace homesec {

class FaceHolder
{
public:
  static shared_ptr<Face>
  get();

private:
  FaceHolder()
  {
    m_face = make_shared<Face>();
  }

private:
  shared_ptr<Face> m_face;
};

} // namespace homesec
} // namespace ndn


#endif //HOMESEC_FACEHOLDER_HPP
