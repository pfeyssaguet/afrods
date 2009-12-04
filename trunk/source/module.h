#ifndef __MODULE_H__
#define __MODULE_H__

class Module {
	public:
		/** Constructeur et Destructeur */
		Module();
		virtual ~Module() {};

		/** Méthode de mise à jour du module */
		virtual void moduleEvents() {};

		/** Accesseur pour savoir si le module demande à être stoppé */
		bool isStopped();

	protected:
		bool m_bIsStopped;
};

#endif
