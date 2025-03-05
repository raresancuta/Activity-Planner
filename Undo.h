#pragma once
#include "Domain.h"
#include "Repository.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
private:
	Activitate act_adaugata;
	Repo& repo;
public:
	UndoAdauga(Repo& repo, const Activitate& act) :repo{ repo }, act_adaugata{ act } {

	}

	void doUndo() override {
		repo.sterge(act_adaugata.get_id());
	}
	/*
		realizeaza undo petru functionalitatea de adauga
	*/
};

class UndoSterge :public ActiuneUndo {
private:
	Activitate act_stearsa;
	Repo& repo;
public:
	UndoSterge(Repo& repo, const Activitate& act) :repo{ repo }, act_stearsa{ act } {

	}

	void doUndo() override {
		repo.stocheaza(act_stearsa);
	}
	/*
		realizeaza undo petru functionalitatea de sterge
	*/
};

class UndoModifica :public ActiuneUndo {
private:
	Activitate act_modificata;
	Repo& repo;
public:
	UndoModifica(Repo& repo, const Activitate& act) :repo{ repo }, act_modificata{ act } {

	}

	void doUndo() override {
		repo.sterge(act_modificata.get_id());
		repo.stocheaza(act_modificata);
	}
	/*
		realizeaza undo petru functionalitatea de modifica
	*/
};