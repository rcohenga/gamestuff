/*
 * View.hpp
 *
 *  Created on: Dec 15, 2020
 *      Author: raphael
 */

#ifndef HEXAGO_SRC_VIEW_HPP_
#define HEXAGO_SRC_VIEW_HPP_

#include <memory>

#include "Model.hpp"

namespace HexaGo
{

class View
{
public:
    View(std::shared_ptr<Model> model);

    void start();

private:
    std::shared_ptr<Model> m_model;
};

} // namespace HexaGo

#endif /* HEXAGO_SRC_VIEW_HPP_ */
