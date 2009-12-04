#ifndef __MODULE_H__
#define __MODULE_H__

class Module {
	public:
		/** Constructeur et Destructeur */
		Module();
		virtual ~Module() {};

		/** M�thode de mise � jour du module */
		virtual void moduleEvents() {};

		/** Accesseur pour savoir si le module demande � �tre stopp� */
		bool isStopped();

	protected:
		bool m_bIsStopped;
};

#endif
