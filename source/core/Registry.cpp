/*
 * =====================================================================================
 *
 *       Filename:  Registry.cpp
 *
 *    Description:
 *
 *        Created:  23/06/2018 22:43:56
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "BlockWater.hpp"
#include "ItemBlock.hpp"
#include "Registry.hpp"

Registry *Registry::s_instance = nullptr;

void Registry::registerBlocks() {
	registerBlock<Block>(BlockType::Air,         0);
	registerBlock<Block>(BlockType::Dirt,        37);
	registerBlock<Block>(BlockType::Cobblestone, 38);
	registerBlock<Block>(BlockType::Grass,       226);
	registerBlock<Block>(BlockType::Leaves,      266);
	registerBlock<Block>(BlockType::Wood,        277);
	registerBlock<Block>(BlockType::Stone,       402);
	registerBlock<Block>(BlockType::Sand,        369);
	registerBlock<BlockWater>();
	registerBlock<Block>(BlockType::Glass,       168);
	registerBlock<Block>(BlockType::CoalOre,     36);
	registerBlock<Block>(BlockType::Planks,      316);
}

void Registry::registerItems() {
	registerItem<ItemBlock>(ItemType::Air,         BlockType::Air);
	registerItem<ItemBlock>(ItemType::Dirt,        BlockType::Dirt);
	registerItem<ItemBlock>(ItemType::Cobblestone, BlockType::Cobblestone);
	registerItem<ItemBlock>(ItemType::Grass,       BlockType::Grass);
	registerItem<ItemBlock>(ItemType::Leaves,      BlockType::Leaves);
	registerItem<ItemBlock>(ItemType::Wood,        BlockType::Wood);
	registerItem<ItemBlock>(ItemType::Stone,       BlockType::Stone);
	registerItem<ItemBlock>(ItemType::Sand,        BlockType::Sand);
	registerItem<ItemBlock>(ItemType::Water,       BlockType::Water);
	registerItem<ItemBlock>(ItemType::Glass,       BlockType::Glass);
	registerItem<ItemBlock>(ItemType::CoalOre,     BlockType::CoalOre);
	registerItem<ItemBlock>(ItemType::Planks,      BlockType::Planks);

	registerItem<Item>(ItemType::Stick,        324);
	registerItem<Item>(ItemType::StoneAxe,     325);
	registerItem<Item>(ItemType::StoneHoe,     326);
	registerItem<Item>(ItemType::StonePickaxe, 327);
	registerItem<Item>(ItemType::StoneShovel,  328);
	registerItem<Item>(ItemType::StoneSword,   329);

	// FIXME: Move this to Application or load from XML file
	registerRecipes();
}

void Registry::registerRecipes() {
	m_recipes.emplace_back(std::array<u32, 9>{6, 6, 0, 6, 12, 0, 0, 12, 0}, ItemStack{ItemType::StoneAxe});
	m_recipes.emplace_back(std::array<u32, 9>{6, 6, 0, 0, 12, 0, 0, 12, 0}, ItemStack{ItemType::StoneHoe});
	m_recipes.emplace_back(std::array<u32, 9>{6, 6, 6, 0, 12, 0, 0, 12, 0}, ItemStack{ItemType::StonePickaxe});
	m_recipes.emplace_back(std::array<u32, 9>{0, 6, 0, 0, 12, 0, 0, 12, 0}, ItemStack{ItemType::StoneShovel});
	m_recipes.emplace_back(std::array<u32, 9>{0, 6, 0, 0, 6, 0, 0, 12, 0},  ItemStack{ItemType::StoneSword});

	m_recipes.emplace_back(std::array<u32, 9>{5, 0, 0, 0, 0, 0, 0, 0, 0},   ItemStack{ItemType::Wood, 4}, true);
	m_recipes.emplace_back(std::array<u32, 9>{11, 11, 0, 0, 0, 0, 0, 0, 0}, ItemStack{ItemType::Stick, 4}, true);
}

const CraftingRecipe *Registry::getRecipe(const Inventory &inventory) const {
	for (const CraftingRecipe &recipe : m_recipes) {
		if (recipe.isMatching(inventory))
			return &recipe;
	}
	return nullptr;
}

