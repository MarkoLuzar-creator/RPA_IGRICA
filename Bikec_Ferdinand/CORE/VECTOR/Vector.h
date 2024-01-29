#pragma once
#include <vector>
#include "../../IGRA/StaticSlika.h"
#include "../../IGRA/Arena.h"
#include "../../IGRA/Nasprotnik.h"

class Vector{
public:
	static Vector& GetInstance() {
		static Vector instance;
		return instance;
	}
	//std::vector<KlasičniGumb*> m_SeznamKlasičnihGumbov;
	std::vector<StaticSlika*> m_SeznamStatičnihSlik;
	std::vector<Arena*> m_SeznamAren;
	std::vector<Nasprotnik*> m_SeznamNasprotnikov;
private:
	Vector(){}
};

