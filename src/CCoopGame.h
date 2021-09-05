#pragma once
#include "CGAME.h"
#include "CPlayer.h"


class CCoopGame : public CGame, public enable_shared_from_this<CCoopGame>{
public:
	CCoopGame() = default;
	~CCoopGame() = default;

	void welcome()const override;
	void GAMEOVER() const override;
	void VICTORY() const override;
	void addDifficulty() override;
	void savegame() override;
	void addPlayers() override;
	void start() override;
	void fillStorage();
	void loadPlayers(CTokenReader&);


	vector<CPlayer> m_Players;

};

