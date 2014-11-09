[ ] write tests for World, pay attention to entity destruction
[ ] add an ability to remove a System (?)
[ ] review TagManager & GroupManager code
[ ] finish entity tests
[ ] write tests for TagManager
[ ] write a doc-comments

NOTES:
- be carefull not add the same component (pointer) twice / to several entities,
    it'll break shit cuz the pointer to it will be deleted by the removeComponent method,
    although nothing stops you from doing this, so watch out

- systems should be added before entities & their components
