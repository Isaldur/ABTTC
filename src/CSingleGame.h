#pragma once
#include "CGAME.h"
#include "CPlayer.h"


class CSingleGame : public CGame, public enable_shared_from_this<CSingleGame>{
public:
	CSingleGame() = default;
	
	void welcome()const override;
	void VICTORY() const override;
	void GAMEOVER() const override;
	void savegame() override;
	void addDifficulty() override;
	void addPlayers() override;
	void start() override;
	void fillStorage();
	void loadPlayers(CTokenReader&);

	CPlayer m_Player;
};

