module Data.Calendar where

import Prelude

-- https://github.com/purescript/purescript/wiki/Language-Guide#importing-modules
import Data.List(List(..), filter, head, mapMaybe)
--     ... esp when the `Maybe` typeclass doesn't use the (..) notation
import Data.Maybe (Maybe, fromJust)
import Data.Int(toNumber)
import Data.DateTime(DateTime(..), Date(..), Time(..),
                     Hour, Minute, Second, Millisecond,
                     Year, Month, Day,
                     date, time, exactDate)
import Data.Enum(toEnum)
import Control.Plus (empty)
import Partial.Unsafe(unsafePartial)

type CalendarEntry = {
  name :: String
  , description :: String
  , start :: DateTime
  , end :: DateTime
  }

type CalendarEntries =  List CalendarEntry
type Calendar = CalendarEntries

showCalendarEntry :: CalendarEntry -> String
showCalendarEntry entry =
  entry.name <>
  "\n-------------\n" <>
  entry.description <> "\n" <>
  "from: " <> show entry.start <> "\n" <>
  "til: " <> show entry.end

someTime :: Int -> Int -> Time
someTime hr min =
  Time anHr aMin aSec aMs
  where
    anHr = unsafePartial(fromJust (toEnum hr :: Maybe Hour))
    aMin = unsafePartial(fromJust (toEnum min :: Maybe Minute))
    aSec = unsafePartial(fromJust (toEnum 0 :: Maybe Second))
    aMs = unsafePartial(fromJust (toEnum 0 :: Maybe Millisecond))

someDate :: Int -> Int -> Int -> Date
someDate yr mo dy =
  unsafePartial $ fromJust $ exactDate aYear aMonth aDay
  where
    aYear = unsafePartial(fromJust (toEnum yr :: Maybe Year))
    aMonth = unsafePartial(fromJust (toEnum mo :: Maybe Month))
    aDay = unsafePartial(fromJust (toEnum dy :: Maybe Day))

testEntryOne :: CalendarEntry
testEntryOne = {
  name: "fellowship"
  , description: "much talking"
  , start: DateTime (someDate 2016 8 27) (someTime 20 0)
  , end: DateTime (someDate 2016 8 28) (someTime 6 0)
  }

testEntryTwo :: CalendarEntry
testEntryTwo = {
  name: "programming"
  , description: "code much?"
  , start: DateTime (someDate 2016 8 29) (someTime 8 0)
  , end: DateTime (someDate 2016 8 29) (someTime 18 0)
  }


emptyCalendar :: Calendar
emptyCalendar = empty

-- noting eta conversion
insertEntry :: CalendarEntry -> Calendar -> Calendar
insertEntry = Cons

-- noting infix operator
myCalendar = insertEntry testEntryTwo $
             insertEntry testEntryOne emptyCalendar

allEntries :: Calendar -> CalendarEntries
allEntries calendar = calendar

-- noting function composition
entriesOnDate :: Date -> Calendar -> CalendarEntries
entriesOnDate meiDay =
  (filter filterEntry) <<< allEntries
  where
    filterEntry :: CalendarEntry -> Boolean
    filterEntry entry =
      (date entry.start) == meiDay ||
      ((date entry.end) == meiDay &&
       (not ((time entry.end) == (someTime 0 0)))) ||
      ((date entry.start) < meiDay && (date entry.end) > meiDay)
