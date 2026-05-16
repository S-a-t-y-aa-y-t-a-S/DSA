## Weekly Sprint logs

### Sprint 2: AVL ROTATION AFTER DELETION (Week 2 - May 2026)
**Epic:** [DSA-1] avl rotation after deletion<br>
**Sprint Summary Wins:** 
- [to be filled by the end of this week]<br>
**Sprint summary blockages:** 
- [to be filled by the end of this week]


#### Daily Standup Records (Click to expand)
<details>
<summary><b>Day 6 (16 May 2026)</b></summary>
<b>Objective:</b><br>learning about 2-3-trees<br> 
<b>Wins:</b><br>understanding insertion operation on paper<br>
<b>Blockages:</b><br>implementation of insertion operation in 2-3-trees<br>
</details>
<details>
<summary><b>Day 5 (15 May 2026)</b></summary>
<b>Objective:</b><br>adding searching functionality<br> 
<b>Wins:</b><br>searching for a key in 2-3-trees is done and a stack push is added<br>
<b>Blockages:</b><br>implementation of insertion the key if not found<br>
</details>
<details>
<summary><b>Day 4 (14 May 2026)</b></summary>
<b>Objective:</b><br>learning about 2-3-trees<br> 
<b>Wins:</b><br>implementation of special cases of inserting a key to a node where loop is not used yet<br>
<b>Blockages:</b><br>1) loop shall be used and be running until the stack does not become emmpty<br>2) connecting the new parent node to the given node's previous parent node<br>3) adding a sibling node to the given node so that the new parent node shall connect to both<br>
</details>
<details>
<summary><b>Day 3 (13 May 2026)</b></summary>
<b>Objective:</b><br>testing out rotation in worst cases<br> 
<b>Wins:</b><br>deletion operation in avl tree is done<br>
<b>Blockages:</b><br>cutting off the branch of sub-tree by assigning null to its child node, depending on the traversal the child is left or right<br>
</details>
<details>
<summary><b>Day 2 (12 May 2026)</b></summary>
<b>Objective:</b><br>resolving segmentation fault<br> 
<b>Wins:</b><br>successfully resolved segmentation fault and completed deletion operation<br>
<b>Blockages:</b><br>need to check for a resultant tree which stays unbalanced after deletion<br>
</details>
<details>
<summary><b>Day 1 (11 May 2026)</b></summary>
<b>Objective:</b><br>storing the nodes in stack<br> 
<b>Wins:</b><br>able to search the given key, store all the nodes traversed in stack which helped to get the successor and its parent node<br>
<b>Blockages:</b><br>facing segmentation fault thereafter while checking for balance factor<br>
</details>

---

### Sprint 1: AVL ROTATION AFTER DELETION (Week 1 - May 2026)
**Epic:** [DSA-1] avl rotation after deletion<br>
**Sprint Summary Wins:**<br>
1) replaced current node's data with successor.
2) removed the physical node of the successor and connected its parent to its child.<br>

**Sprint Summary Blockages:**<br>
1) need to traverse from parent of the parent of the successor node back to the root node.
2) checking each of their balance factor for rotation

#### Daily Standup Records (Click to expand)
<details>
<summary><b>Day 1 (5 May 2026)</b></summary>
<b>Objective:</b><br>connecting GITHUB repo to JIRA<br> 
<b>Wins:</b><br>successfully created a branch and using smart commit shifted card from To Do to In Progress<br>
<b>Blockages:</b><br>tried KANBAN template. SCRUM template suited the most<br>
</details>
<details>
<summary><b>Day 2 (10 May 2026)</b></summary>
* <b>Objective:</b><br>replace the current node's data with successor<br> 
* <b>Wins:</b><br>able to replace current nodes's data with successor. removed the physical node of the successor and connected its parent to its child<br>
* <b>Blockages:</b><br>need to traverse from parent of the successor node back to the root node and checking each of their balance factor for rotation.
</details>

