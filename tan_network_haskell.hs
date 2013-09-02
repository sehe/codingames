import Data.Maybe
import Data.Char
import Data.List
import qualified Data.Map as M
import Data.String.Utils
import Control.Applicative
import Debug.Trace

type LatLong = (Double, Double)
data Stop    = Stop String String LatLong deriving(Eq,Ord,Show,Read)
type Edge    = (String,String)
type Datum   = Either Stop Edge
type Storage = ([Stop],[Edge])

parse     :: [String]     -> Storage -> Storage
store     :: Maybe Datum  -> Storage -> Storage
parseLine :: String       -> Maybe Datum

parse ([])        storage = storage
parse (line:rest) storage = store (parseLine line) (parse rest storage)

store Nothing storage                  = storage
store (Just (Right edge)) (stops, edges) = (stops, edge:edges)
store (Just (Left  stop)) (stops, edges) = (stop:stops, edges)

parseLine line 
  | 9 == (length $ split "," line) = 
            let presplit = (split "\"" line) in
            let fullname = presplit!!1 in
            let stopid   = (split "," (presplit!!0))!!0 in
            let lat      = read $ (split "," (presplit!!2))!!2 in
            let long     = read $ (split "," (presplit!!2))!!3 in
            Just $ Left $ Stop stopid fullname (lat, long)
  | 2 == (length $ words line)       = 
            let from:to:[] = words line in Just $ Right (to, from)
  | otherwise = Nothing -- disregard

makeEdge :: Edge
makeEdge = ("0","0") :: Edge

distance :: LatLong -> LatLong -> Double
distance (latitudeA, longitudeA) (latitudeB, longitudeB) = sqrt (x*x + y*y) * 6371
                where x = (longitudeB - longitudeA) * cos( (latitudeA+latitudeB) / 2.0)
                      y = (latitudeB - latitudeA)

getLatlong :: Stop -> LatLong
getLatlong (Stop _ _ latlong) = latlong

getStopId :: Stop -> String
getStopId (Stop id _ _) = id

getStopName :: Stop -> String
getStopName (Stop _ fullname _) = fullname

type RichEdge  = (Stop, Stop, Double)
type RichEdges = [RichEdge]
type Solution  = [String]

findSolutions :: String -> String -> RichEdges -> [[String]]
findSolutions start dest edges
   | start == dest = [[start]]
   | otherwise = 
         concat . fmap (recurse start edges) $ (incoming dest edges) 
         where
            incoming :: String -> RichEdges -> [String] -- enumerate incoming edges for destination
            incoming dest edges = do
                    let ids = getStopId . src <$> filter (by_dest dest) edges
                    trace ("incoming " ++ (show dest) ++ " edges: " ++ (show ids)) $ ids
                    where 
                          by_dest d (to,_,_) = (d == getStopId to)
                          src (_,from,_)     = from
            --
            recurse :: String -> RichEdges -> String -> [[String]]
            recurse start edges dest = 
                [[start,dest]]
                {-concat . fmap (recurse start edges) $ (incoming dest edges) -}

main = do
    contents <- getContents
    let start:end:graphdata = lines contents
    let graph               = parse graphdata ([],[])
    let stopmap             = 
            mapped :: M.Map String Stop
            where mapped    = M.fromList $ fmap (\stop@(Stop id _ _) -> (id, stop)) stops 
                  (stops,_) = graph
    let edges               = 
            fmap (\(to,from) -> (to, from, (distance (getLatlong to) (getLatlong from)))) edges__
            where edges__    = fmap (\(to,from) -> (stopmap!to, stopmap!from)) edges_
                  (_,edges_) = graph
                  (!) = (M.!)
    let proximity = distance (getLatlong $ stopmap M.! start) . getLatlong
    let sorted_edges = sortBy (\(_, a, _) (_, b, _) -> (proximity a) `compare` (proximity b)) edges

    {-let (stops, _) = graph-}
    {-putStrLn $ start-}
    {-putStrLn $ end-}
    {-putStrLn $ show (M.size stopmap)-}
    {-putStrLn $ concat . intersperse "\n"  $ (fmap (\(Stop id fname (lat,long)) -> id ++ ",\"" ++ fname ++ "\",," ++ (show lat) ++ "," ++ (show long) ++ ",,,1,") stops)-}
    {-putStrLn $ show (length edges)-}
    {-putStrLn $ concat . intersperse "\n"  $ (fmap (\(to,from,_) -> (getStopId from) ++ " " ++ (getStopId to)) edges)-}
    putStrLn $ concat . intersperse "\n-----------\n" $ dumpSolution stopmap <$> findSolutions start end edges
        where
           dumpSolution :: M.Map String Stop -> [String] -> String
           dumpSolution stopmap solution = concat . intersperse "\n" $ show <$> (stopmap M.!) <$> solution
