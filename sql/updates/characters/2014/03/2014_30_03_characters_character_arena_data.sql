ALTER TABLE `character_arena_data`
    ADD COLUMN `rating3` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `seasonWins2`,
	ADD COLUMN `bestRatingOfWeek3` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `rating3`,
	ADD COLUMN `bestRatingOfSeason3` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `bestRatingOfWeek3`,
	ADD COLUMN `matchMakerRating3` INT(10) NOT NULL DEFAULT 1500 AFTER `bestRatingOfSeason3`,
	ADD COLUMN `weekGames3` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `matchMakerRating3`,
	ADD COLUMN `weekWins3` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `weekGames3`,
	ADD COLUMN `prevWeekWins3` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `weekWins3`,
	ADD COLUMN `seasonGames3` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `prevWeekWins3`,
	ADD COLUMN `seasonWins3` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `seasonGames3`;