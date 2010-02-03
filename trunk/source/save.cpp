#include "save.h"
#include "itemweapon.h"
#include "itemarmor.h"
#include "constants.h"
#include <fat.h>


using namespace AfroDS;

Save * Save::m_Instance = NULL;

/**
 * Constructeur par défaut
 */
Save::Save() {
	/*
	// Initialisation du filesystem (c'est pas gagné)
	PA_OutputText(ECRAN_HAUT, 1, 5, "Init. FAT...");
	if (!fatInitDefault()) {
		// FAT ne fonctionne pas, on est mal...
		PA_OutputText(ECRAN_HAUT, 27, 5, "[KO]");
		PA_OutputText(ECRAN_HAUT, 4, 21, "FAT system is down");
	} else {
		// FAT fonctionne
		PA_OutputText(ECRAN_HAUT, 27, 5, "[OK]");
	}
	// Chargement des persos depuis la sauvegarde
	PA_OutputText(ECRAN_HAUT, 1, 6, "Init. personnages...");
	*/
	loadCharacters();
}

Save * Save::getInstance() {
	if (m_Instance == NULL) {
		// Initialisation de la sauvegarde
		m_Instance = new Save();
	}
	return m_Instance;
}

/**
 * Renvoie le nombre de personnages de la sauvegarde
 * @return int nombre de personnages
 */
int Save::getNbCharacters() {
	return m_characters.size();
}

/**
 * Crée un nouveau personnage
 * @param Character newchar personnage à créer
 */
void Save::addCharacter(CharacterPlayer * newchar) {
	m_characters.push_back(newchar);
}

/**
 * Récupère le personnage n° N
 * @param int iNumPerso numéro du personnage
 * @return Character personnage
 */
CharacterPlayer * Save::getCharacter(int iNumPerso) {
	return m_characters.at(iNumPerso);
}

/**
 * Crée un perso de test pour utiliser directement en jeu
 */
CharacterPlayer * Save::getDemoCharacter() {
	CharacterPlayer * deuspi = new CharacterPlayer("deuspi");
	deuspi->addItemToInventory(new Item("Heal Potion", TYPE_POTION_HEAL, 20));
	deuspi->addItemToInventory(new Item("Poil de uque"));
	deuspi->addItemToInventory(new ItemWeapon("Shortbow", TYPE_RANGEDWEAPON, Coords(1, 6)));
	deuspi->addItemToInventory(new ItemWeapon("Sword of Boulbi", TYPE_WEAPON_SWORD, Stats(2, 0, 12, 0, 0, 0), Coords(1, 10), LARGEICON_SWORD_1));
	deuspi->addItemToInventory(new ItemArmor("Leather armor", TYPE_ARMOR, 2));
	//deuspi->addItemToInventory(new ItemWeapon("Dagger", TYPE_WEAPON_DAGGER, Stats(1, 0, 2, 0, 0, 0), Coords(1, 4)));
	//deuspi->addItemToInventory(new ItemWeapon("Greatsword", TYPE_LARGEWEAPON, Coords(2, 6)));
	//deuspi->addItemToInventory(new ItemWeapon("Handaxe", TYPE_WEAPON_AXE, Coords(1, 6)));
	//deuspi->addItemToInventory(new ItemWeapon("Warhammer", TYPE_WEAPON_HAMMER, Coords(1, 8)));
	//deuspi->addItemToInventory(new ItemArmor("Cloak", TYPE_CLOAK));
	//deuspi->addItemToInventory(new ItemArmor("Helmet", TYPE_HELMET));
	//deuspi->addItemToInventory(new ItemArmor("Shield", TYPE_SHIELD));
	deuspi->addItemToInventory(new Item("Mana Potion", TYPE_POTION_MANA, 15));

	// équipement
	//character.addItemToEquipment(SLOT_RIGHT_WEAPON, new Item("Hache", TYPE_RIGHT_WEAPON, Stats()));
	deuspi->addItemToEquipment(SLOT_HELMET, new ItemArmor("Helmet", TYPE_HELMET, 2));
	deuspi->addItemToEquipment(SLOT_CLOAK, new ItemArmor("Cloak", TYPE_CLOAK, 1));
	deuspi->addItemToEquipment(SLOT_ARMOR, new ItemArmor("Bronze armor", TYPE_ARMOR, 6, Stats(4, 4, 4, 0, 0, 0)));
	deuspi->addItemToEquipment(SLOT_RIGHT_WEAPON, new ItemWeapon("Dwarven axe", TYPE_WEAPON_AXE, Coords(1, 10)));
	deuspi->addItemToEquipment(SLOT_LEFT_WEAPON, new ItemWeapon("Bastard sword", TYPE_WEAPON_SWORD, Coords(1, 10)));
	deuspi->addItemToEquipment(SLOT_BOOTS, new ItemArmor("Boots", TYPE_BOOTS, 2));
	deuspi->addItemToEquipment(SLOT_GLOVES, new ItemArmor("Gloves", TYPE_GLOVES));
	deuspi->addItemToEquipment(SLOT_RIGHT_RING, new Item("Ring", TYPE_RING));
	deuspi->addItemToEquipment(SLOT_LEFT_RING, new Item("The One Ring", TYPE_RING, LARGEICON_RING_GOLD));
	deuspi->addItemToEquipment(SLOT_BELT, new Item("Belt", TYPE_BELT));
	deuspi->addItemToEquipment(SLOT_NECKLACE, new Item("Necklace", TYPE_NECKLACE));

	deuspi->addMoney(564941);
	return deuspi;
}


/**
 * Charge les personnages depuis la sauvegarde
 */
void Save::loadCharacters() {
/*
	FILE* file = fopen(AFRODS_SAVE_FILENAME, "r");

	if (file) {
		//on cherche la taille du fichier, cela sert apres pour le buffer
		u32 size;
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		rewind(file);//on retourne au debut du fichier

		// on alloue suffisamment de mémoire et on stocke l'adresse dans buffer
		char * buffer;
		buffer = (char*) malloc(sizeof(char) * size);
		fread(buffer, 1, size, file);
//		PA_OutputText(ECRAN_HAUT, 4, 8, "content: [%s]", buffer);
//		PA_OutputText(ECRAN_HAUT, 4, 9, "size: %d bytes", size);
		free(buffer);
		fclose(file);//on ferme le fichier
	} else {
		// on crée un nouveau fichier
		file = fopen(AFRODS_SAVE_FILENAME, "wb");
		fclose(file);//on ferme le fichier
	}
	*/
	// pour l'instant j'ajoute quelques persos bidons pour test
	createDemoCharacters();
}

/**
 * Sauvegarde les personnages
 */
void Save::saveCharacters() {
	/*
	Character charac;
	for(std::vector<Character>::iterator it = m_characters.begin(); it != m_characters.end(); ++it)
		charac = (Character)it;
		std::string sPath = "/" + charac.getName() + ".dat";
		if (m_UseEFS)
			sPath = "efs:" + sPath;
		FILE * file = fopen(sPath, "wb");
		fwrite((void *)charac, 1, sizeof(charac), file);
		fclose(file);
	}
	*/

}


/**
 * Crée une liste de persos de test pour utiliser dans le menu
 */
void Save::createDemoCharacters() {
	addCharacter(getDemoCharacter());

	addCharacter(new CharacterPlayer("Warrior", CLASS_WARRIOR));
	addCharacter(new CharacterPlayer("Wizard", CLASS_WIZARD));
	addCharacter(new CharacterPlayer("Ranger", CLASS_RANGER));
	addCharacter(new CharacterPlayer("Priest", CLASS_PRIEST));
	addCharacter(new CharacterPlayer("Monk", CLASS_MONK));

}
