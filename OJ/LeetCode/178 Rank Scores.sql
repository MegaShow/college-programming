SELECT Scores.Score, count(Ranks.Score) AS Rank
FROM Scores, (SELECT DISTINCT Score FROM Scores) AS Ranks
WHERE Ranks.Score >= Scores.Score
GROUP BY Scores.Id
ORDER BY Scores.Score DESC
