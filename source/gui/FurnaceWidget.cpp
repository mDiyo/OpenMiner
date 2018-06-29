/*
 * =====================================================================================
 *
 *       Filename:  FurnaceWidget.cpp
 *
 *    Description:
 *
 *        Created:  28/06/2018 10:03:06
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "FurnaceWidget.hpp"

FurnaceWidget::FurnaceWidget(Inventory &playerInventory, Inventory &hotbarInventory, BlockData &blockData, Widget *parent)
	: Widget(176, 166, parent), m_playerInventory(playerInventory), m_hotbarInventory(hotbarInventory), m_blockData(blockData)
{
	m_background.load("texture-furnace");
	m_background.setClipRect(0, 0, 176, 166);

	m_playerInventoryWidget.init(m_playerInventory);
	m_playerInventoryWidget.setPosition(7, 83, 0);

	m_hotbarInventoryWidget.init(m_hotbarInventory);
	m_hotbarInventoryWidget.setPosition(7, 141, 0);

	m_inputInventoryWidget.setPosition(55, 16, 0);
	m_outputInventoryWidget.setPosition(115, 34, 0);
	m_fuelInventoryWidget.setPosition(55, 52, 0);
}

void FurnaceWidget::onEvent(const SDL_Event &event) {
	m_playerInventoryWidget.onMouseEvent(event, m_mouseItemWidget);
	m_hotbarInventoryWidget.onMouseEvent(event, m_mouseItemWidget);

	m_inputInventoryWidget.onMouseEvent(event, m_mouseItemWidget);
	m_outputInventoryWidget.onMouseEvent(event, m_mouseItemWidget);
	m_fuelInventoryWidget.onMouseEvent(event, m_mouseItemWidget);

	m_mouseItemWidget.onEvent(event);
}

void FurnaceWidget::update() {
	m_inputInventoryWidget.init(m_blockData.inventory, 0, 1);
	m_outputInventoryWidget.init(m_blockData.inventory, 1, 1);
	m_fuelInventoryWidget.init(m_blockData.inventory, 2, 1);

	const ItemWidget *currentItemWidget = nullptr;
	if ((currentItemWidget = m_playerInventoryWidget.currentItemWidget())
	 || (currentItemWidget = m_hotbarInventoryWidget.currentItemWidget())
	 || (currentItemWidget = m_inputInventoryWidget.currentItemWidget())
	 || (currentItemWidget = m_outputInventoryWidget.currentItemWidget())
	 || (currentItemWidget = m_fuelInventoryWidget.currentItemWidget()))
		m_mouseItemWidget.update(currentItemWidget);
	else
		m_mouseItemWidget.update(nullptr);
}

void FurnaceWidget::draw(RenderTarget &target, RenderStates states) const {
	applyTransform(states);

	target.draw(m_background, states);

	target.draw(m_playerInventoryWidget, states);
	target.draw(m_hotbarInventoryWidget, states);

	target.draw(m_inputInventoryWidget, states);
	target.draw(m_outputInventoryWidget, states);
	target.draw(m_fuelInventoryWidget, states);

	target.draw(m_mouseItemWidget, states);
}

