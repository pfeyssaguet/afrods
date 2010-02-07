#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "item.h"
#include "itemweapon.h"
#include "itemarmor.h"
#include "types.h"

#include <string>
#include <map>
#include <vector>

#define StatModifier(stat) (((stat) / 2) - 5)

namespace AfroDS {
	/**
	 * Les différents slots d'équipement
	 * - Tête : casque ou chapeau
	 * - Dos : cape
	 * - Corps : armure
	 * - Main droite : arme
	 * - Main gauche : bouclier ou indispo si arme à 2 mains
	 * - Pieds : bottes
	 * - Mains : gants
	 * - Doigt droit : anneau
	 * - Doigt gauche : anneau
	 * - Cou : amulette
	 * - Taille : ceinture
	 * le dernier élément SLOT_SIZE sert à connaître le nombre de slots
	 * ou à indiquer un item sans slot (non équipable)
	 */
	enum EquipmentSlot {
		SLOT_HELMET,
		SLOT_CLOAK,
		SLOT_ARMOR,
		SLOT_RIGHT_WEAPON,
		SLOT_LEFT_WEAPON,
		SLOT_BOOTS,
		SLOT_GLOVES,
		SLOT_RIGHT_RING,
		SLOT_LEFT_RING,
		SLOT_NECKLACE,
		SLOT_BELT,
		SLOT_SIZE // un faux slot qui permet de compter le nombre de slots, et aussi d'indiquer qu'un item ne s'équipe pas
	};


	/**
	 * Représente un personnage
	 */
	class Creature {
		public:
			virtual ~Creature();

			/**
			 * Renvoie le nom du personnage
			 * @return std::string nom du personnage
			 */
			std::string getName() const;

			/**
			 * Définit le nom du personnage
			 * @param std::string sName nom du personnage
			 */
			void setName(const std::string sName);

			/**
			 * Renvoie les stats de base du personnage, sans bonus
			 * @return Stats stats de base du perso
			 */
			Stats getBaseStats() const;

			long getCurrentHp() const;
			void setCurrentHp(const int hp);
			long getCurrentMp() const;
			void setCurrentMp(const int mp);
			long getMaxHp() const;
			long getMaxMp() const;

			void addMoney(const long money);
			void subMoney(const long money);
			long getMoney() const;

			/**
			 * Ajoute un item dans l'équipement
			 * @param EquipmentSlot slot slot dans lequel équiper l'item
			 * @param Item * item item à équiper (pointeur)
			 */
			void addItemToEquipment(const EquipmentSlot slot, Item * item);

			/**
			 * Renvoie l'item d'équipement correspondant au slot demandé
			 * @param EquipmentSlot slot slot demandé
			 * @return Item * item d'équipement (pointeur)
			 */
			Item * getEquipmentItem(const EquipmentSlot slot) const;

			int attack(Creature * target);

			int getBonusAttack() const;
			int getArmorClass() const;

			/**
			 * Ajoute un item dans l'inventaire
			 * @param Item item l'item à ajouter
			 */
			void addItemToInventory(Item * item);

			/**
			 * Renvoie l'item n° N de l'inventaire
			 * @param int iNumItem numéro de l'item à récupérer
			 * @return Item item récupéré
			 */
			Item * getInventoryItem(const int iNumItem);

			Item * getInventoryItem(const int iNumItem, bool extract);

			void deleteInventoryItem(const int iNumItem);

			/**
			 * Renvoie le nombre d'items dans l'inventaire
			 * @return int nombre d'items
			 */
			unsigned int getInventorySize() const;

			/**
			 * Equipe un item de l'inventaire si possible, et renvoie true en cas de succès
			 * @param unsigned int iNumItem numéro de l'item d'inventaire
			 * @return bool false en cas d'échec
			 */
			bool equipItem(const unsigned int iNumItem);

			/**
			 * Retire un item d'équipement et le remet dans l'inventaire
			 * @param EquipmentSlot slot slot d'équipement à vider
			 * @return bool false en cas d'échec
			 */
			bool unequipItem(const EquipmentSlot slot);

			void activateInventoryItem(const unsigned int iNumItem);

			bool activateItem(Item * item);

			/**
			 * Renvoie les stats du personnage, avec les bonus et modificateurs appliqués
			 * @return Stats stats du personnage
			 */
			virtual Stats getStats() const = 0;

			virtual int rollAttack() const;

			/**
			 * Méthode statique utilitaire permettant de traduire un slot
			 * en string pour l'afficher dans le menu (comme un toString() pour
			 * l'enum EquipmentSlot)
			 * @param EquipmentSlot slot à traduire
			 * @return std::string chaîne de caractères
			 */
			static std::string translateSlot(const EquipmentSlot slot, const bool shortName);

			static std::string translateSlot(const EquipmentSlot slot);

			static int XpToLevel(const long xp);

			static long XpForNextLevel(const long xp);

		protected:
			/**
			 * Constructeur initialisant le nom
			 * @param std::string sName nom du personnage
			 */
			Creature(const std::string sName = "");

			/** Nom du personnage */
			std::string m_sName;

			/** Stats de base */
			Stats m_baseStats;

			/** Pts de vie max */
			long m_maxHp;

			/** Pts de vie courants */
			long m_currentHp;

			/** Pts de mana max */
			long m_maxMp;

			/** Pts de mana courants */
			long m_currentMp;

			/** Argent */
			long m_money;

			/** Inventaire */
			std::vector<Item *> m_inventory;

			/** Equipement */
			std::map<EquipmentSlot, Item *> m_equipment;
	};

}

#endif
