BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS `minigameScores` (
	`ID`	INT NOT NULL,
	`name`	VARCHAR ( 30 ),
	`hangman`	INT,
	`brickBreaker`	INT,
	`hazarGame`	INT,
	`danGame`	INT,
	`patrykGame`	INT,
	PRIMARY KEY(`ID`)
);
INSERT INTO `minigameScores` VALUES (1,'Nick',100,200,300,400,500);
CREATE TABLE IF NOT EXISTS `mainGamePlayer` (
	`ID`	INT NOT NULL,
	`name`	VARCHAR ( 30 ),
	`cash`	INT,
	`strikes`	INT,
	`bank`	INT,
	`lastOnline`	DATE,
	`score`	INT,
	PRIMARY KEY(`ID`)
);
INSERT INTO `mainGamePlayer` VALUES (1,'Nick',300,0,7000,2012,1300);
INSERT INTO `mainGamePlayer` VALUES (2,'Dan',2300,2,3000,'2018-02-24',1700);
COMMIT;
