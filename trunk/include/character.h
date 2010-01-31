#ifndef __CHARACTER_H__
#define __CHARACTER_H__

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
	 * Les diff�rents slots d'�quipement
	 * - T�te : casque ou chapeau
	 * - Dos : cape
	 * - Corps : armure
	 * - Main droite : arme
	 * - Main gauche : bouclier ou indispo si arme � 2 mains
	 * - Pieds : bottes
	 * - Mains : gants
	 * - Doigt droit : anneau
	 * - Doigt gauche : anneau
	 * - Cou : amulette
	 * - Taille : ceinture
	 * le dernier �l�ment SLOT_SIZE sert � conna�tre le nombre de slots
	 * ou � indiquer un item sans slot (non �quipable)
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
		SLOT_SIZE // un faux slot qui permet de compter le nombre de slots, et aussi d'indiquer qu'un item ne s'�quipe pas
	};


	/**
	 * Repr�sente un personnage
	 */
	class Character {
		public:
			virtual ~Character();

			/**
			 * Renvoie le nom du personnage
			 * @return std::string nom du personnage
			 */
			std::string getName() const;

			/**
			 * D�finit le nom du personnage
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
			 * Ajoute un item dans l'�quipement
			 * @param EquipmentSlot slot slot dans lequel �quiper l'item
			 * @param Item * item item � �quiper (pointeur)
			 */
			void addItemToEquipment(const EquipmentSlot slot, Item * item);

			/**
			 * Renvoie l'item d'�quipement correspondant au slot demand�
			 * @param EquipmentSlot slot slot demand�
			 * @return Item * item d'�quipement (pointeur)
			 */
			Item * getEquipmentItem(const EquipmentSlot slot) const;

			int attack(Character * target);

			int getBonusAttack() const;
			int getArmorClass() const;

			/**
			 * Ajoute un item dans l'inventaire
			 * @param Item item l'item � ajouter
			 */
			void addItemToInventory(Item * item);

			/**
			 * Renvoie l'item n� N de l'inventaire
			 * @param int iNumItem num�ro de l'item � r�cup�rer
			 * @return Item item r�cup�r�
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
			 * Equipe un item de l'inventaire si possible, et renvoie true en cas de succ�s
			 * @param unsigned int iNumItem num�ro de l'item d'inventaire
			 * @return bool false en cas d'�chec
			 */
			bool equipItem(const unsigned int iNumItem);

			/**
			 * Retire un item d'�quipement et le remet dans l'inventaire
			 * @param EquipmentSlot slot slot d'�quipement � vider
			 * @return bool false en cas d'�chec
			 */
			bool unequipItem(const EquipmentSlot slot);

			void activateInventoryItem(const unsigned int iNumItem);

			bool activateItem(Item * item);

			/**
			 * Renvoie les stats du personnage, avec les bonus et modificateurs appliqu�s
			 * @return Stats stats du personnage
			 */
			virtual Stats getStats() const = 0;

			virtual int rollAttack() const;

			/**
			 * M�thode statique utilitaire permettant de traduire un slot
			 * en string pour l'afficher dans le menu (comme un toString() pour
			 * l'enum EquipmentSlot)
			 * @param EquipmentSlot slot � traduire
			 * @return std::string cha�ne de caract�re
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
			Character(const std::string sName = "");

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
