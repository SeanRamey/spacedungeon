# Space Dungeon

A 2D Top-down Scrolling space shooter with a dungeon crawling element.

## Dependencies
- [SFML](https://github.com/SFML/SFML)
- [Doctest](https://github.com/onqtam/doctest)

## Building
The dependencies are taken care of by xrepo. They should be automatically downloaded upon building for the first time.
To build everything, including unit tests:
```
xmake
```
To run both the unit tests and spacedungeon after building:
```
xmake run
```
To run only unit-tests:
```
xmake run unit-tests
```
To run only spacedungeon:
```
xmake run spacedungeon
```
