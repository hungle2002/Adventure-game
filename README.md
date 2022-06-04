# simple_game_C_plus_plus
Chương 3: 
 				Simple C++ game
3.1 Ý tưởng của game:
- Đây là một game thể loại đi ải, người chơi sẽ được cấp ba nhân vật lần lượt là Tank, Warrior và Wizard. Mỗi nhân vật đều có các chỉ số cơ bản là : HP (máu), ATK (công), DEF (thủ) cùng với kĩ năng của từng nhân vật. Trong đó:
+ Tank có thêm chỉ số về giáp : ARM và kĩ năng là tăng giáp (buffARM). Khi bị lần công thì sẽ không trừ trực tiếp vào máu mà sẽ trừ vào giáp trước. Ví dụ đòn tấn công có giá trị là _ATK (_ATK >DEF)
ARM = ARM – (_ATK -DEF).
Nếu ARM < 0 thì :
	HP = HP +ARM
	ARM = 0;
+ Warrior có đặc điểm là có thể tấn công xuyên qua giáp của đối phương cùng với kĩ năng tăng cường ATK trong một lượt tấn công vào kẻ địch.
+ Wizard có đặc điểm là sau khi công qua phần thủ của kẻ địch thì sức mạnh của đòn tấn công sẽ nhân 1.5 lần. Ví dụ kẻ địch có lớp phòng thủ là _DEF thì khi Wizard tấn công vào kẻ địch (_ARM, _HP):
	_ARM = ARM – 1.5*(_ATK - DEF)
Nếu ARM < 0 thì :
	HP = HP +ARM
	ARM = 0;
Kĩ năng của Wizard là đốt trực tiếp vào máu của toàn bộ tất cả kẻ địch một lượng nhất định (tăng theo cấp độ của kĩ năng).
- Các nhân vật chỉ có thể sử dụng kĩ năng duy nhất một lần trong lần trong mỗi chapter, khi qua chapter thì sẽ được khôi phục lại kĩ năng cũng như HP ban đầu và được thưởng một số tiền.
- Người chơi sẽ sử dụng tiền để nâng cấp cấp độ của kĩ năng hoặc vào của hàng để mua các trang bị để tăng chỉ số cho các nhân vật. Các trang bị là:
+ Helmet : tăng chỉ số DEF
+ Armor : tăng chỉ số DEF
+ Weapon: tăng chỉ số ATK
+ DrugArm : hồi phục ARM ( chỉ có thể sử dụng cho Tank)
+ DrugHp : tăng HP 
	- Mỗi nhân vật sẽ có thể trang bị tối đa 1 Helmet, 1 Armor và 1 Weapon. Khi mua trang bị cho nhân vật một trang bị mới thì trang bị cũ sẽ bị tháo ra để cập nhật lại trang bị.
	- Kĩ năng của nhân vật sẽ được chia thành 3 cấp 1,2,3 với các chỉ số tăng lên
+ Tank (buffARM) : 500 -> 700 -> 1000
+ Warrior (buffATK) : 500 -> 700 -> 1000
+ Wizard (attack all) : 200 -> 300 ->500




3.2 Cấu trúc của game:
3.2.1 Sơ đồ cấu trúc của game (file draw.io đính kèm)

 

- Cấu trúc của game sẽ phân thành 3 nhóm chính:
+ Skill : chứa thông tin về kĩ năng (lớp trừu tượng)
+ Item : chứa thông tin về trang bị (lớp trừu tượng)
+ Character: chứa thông tin về nhân vật (lớp trừu tượng)
- Ngoài ra còn các class con cùng với các class:
+ Player : chứa thông tin người chơi
+ Enemy : chứa thông tin về quân địch
+ Store : chứa thông tin của cửa hàng
+ Battle: bao gồm thông tin của kẻ thù và quân địch để tiến hành chơi.
3.2.2 Lớp Skill (trong file skill.h)
 
-Lớp Skill sẽ là lớp trừu tượng, chứa các thông số về
+ state: trạng thái sử dụng (1: chưa dùng, 0: đã dùng)
+ level: cấp của kĩ năng
+ priceToUp : chi phí để nâng cấp kĩ năng
+ num: chỉ số của kĩ năng 
+ Các hàm để kiểm tra các thông số cũng như lấy các chỉ số của kĩ năng
- Lớp Skill sẽ có 3 lớp con sẽ chứa các thông số mặc định cho từng nhân vật cùng với 2 hàm upLevel() và getNextNum() riêng.
+ SkillTank
+ SkillWarrior
+ SkillWizard
3.2.3 Lớp Store và Item (trong file store.h) 
 
-Lớp Item sẽ là lớp trừu tượng, chứa các thông số về
+ price: giá cả của trang bị
+ type : kiểu trang bị
+ các hàm để lấy thông tin của các trang bị
- Các lớp con của lớp Item
+ Helmet : tăng DEF
+ Armor : tăng DEF
+ Weapon : tăng ATK
+ DrugArm : tăng ARM
+ DrugHp : tăng HP
-	Lớp Store sẽ chứa các thông tin về cửa hàng trang bị
+ items [5][3] chứa thông tin của 5 loại trang bị cơ bản cùng với ba cấp độ chất lượng (Basic, Medium, Advance)
+ Hàm printitems() để in ra các trang bị của cửa hàng cùng với giá tiền
 
+ Hàm getItems() để lấy trang bị trong của hàng theo tên 
3.2.4 Lớp Character (trong file store.h) 
 
- Lớp Character là một lớp trừu tượng, chứa các thông tin của các nhân vật trong game về:
+ DEF : chỉ số phòng thủ
+ ATK : chỉ số tấn công
+ HP : máu
+ items[3] : chứa các trang bị (0: Helmet, 1: Armor, 2:Weapon)
+ skill : thông tin về kĩ năng của nhân vật
+ type : kiểu nhân vật
+ các hàm 
. attack: tấn công
. defend: phong thủ
. turnOnSkill : sử dụng kĩ năng
. putOnArmDrug : sử dụng thuốc giáp (chỉ dành riêng cho Tank)
. print: in thông tin của nhân vật
. getARM : lấy chỉ số giáp của nhân vật (chỉ dành riêng cho Tank)
. resetHP : trả về số máu mặc định sau khi qua màn
. putOn: trang bị các vật phẩm (Helmet, Armor, ...)
. alive : kiểm tra xem nhân vật còn sống không 
- Các lớp con của lớp Character lần lượt chứa các chỉ số mặc định và các hàm đặc trưng cho bản thân nhân vật:
+ Tank / Warrior / Wizard
+ Monster
+ Boss 

3.2.5 Lớp Character (trong file store.h) 
 
- Lớp Player: chứa thông tin của người chơi
+ money : số tiền hiện tại của người chơi (dùng để nâng cấp và mua trang bị)
+ phương thức goToStore để đi vào của hàng mua trang bị
+ phương thức hàm earnMoney để cập nhật tiền sau khi qua màn
+ phương thứ checkLoss kiểm tra xem người chơi đã thua chưa (thua khi toàn bộ quân ta đều có HP = 0)
+ phương thức printFull để in thông tin toàn bộ nhân vật của người chơi
+ phương thức printHpArm để in các thông tin về máu và giáp của nhân vật
- Lớp Enemy: chứa các thông tin của quân địch
+ nMonster : số lượng Monster
+ nBoss : số lượng Boss
+ cMon chứa thông tin về các Monster
+ cBoss : chứa thông tin của Boss
+ phương thức attack () tấn công người chơi của enemy
+ phương thức checkWin kiểm tra xem người chơi đã thắng chưa (thắng khi toàn bộ quân địch đều có HP = 0)
+ phương thức printFull để in thông tin toàn bộ nhân vật của quân địch
+ phương thức printHpArm để in các thông tin về máu và giáp của nhân vật
- Lớp Battle chứa các thông tin về trận chiến:
+ player : người chơi
+ enemy : quân địch
+ store : cừa hàng
+ chapters[5] để lưu lại trạng thái, người chơi chỉ có thể thàm gia vào 1 chapter sau khi đã chiến thắng ở chapter trước đó
+ phương thức upLevel() để nâng cấp kĩ năng nhân vật
+ phương thức attackEnemy() để người chơi tấn công quân địch
+ phương thức play() : bắt đầu trò chơi






3.3 Cách chơi:
 
- Đầu tiên khi vào trò chơi sẽ có giao diện giới thiệu cơ bản về cách chơi: 
 
- Người chơi sẽ chọn màn mình muốn tham gia (chỉ có thể tham gia màn khi đã chiến thắng màn trước đó ). Vì vậy khi vừa vào người chơi sẽ chọn màn đầu tiên
 
- Sau khi chọn màn chương trình sẽ in ra các thông số về các nhân vật của người chơi về ATK, DEF, ARM, HP và Level skill cùng với số tiền người chơi đang có (500$ ). Đây là các thông số mặc định của các nhân vật.
* Nâng cấp kĩ năng
- Tiếp theo người chơi sẽ chọn xem có muốn nâng cấp kĩ năng hay không. Nếu muốn sẽ chọn phím 1 và 0 để tiếp tục.
- Giả sử người chơi chọn phím 1 và bắt đầu nâng cấp kĩ năng
 
- Tiếp theo sẽ nhập nhân vật người chơi muốn nâng cấp
 
- Giả sử người chơi chọn nâng cấp kĩ năng cho nhân vật Tank thì lúc này chương trình sẽ in ra giá để nâng cấp, chi phí nâng cấp cùng với trạng thái sau khi nâng cấp kĩ năng. Nếu người chơi chọn nâng cấp thì sẽ nâng cấp nếu người chơi có đủ tiền thì chương trình sẽ in ra nâng cấp thành công nếu không đủ thì sẽ chương trình sẽ báo.
 
- Sau đó người chơi được lựa chọn xem có muốn tiếp tục nâng cấp hay không. Nếu muốn sẽ tiếp tục nâng cấp.
 
*Vào cửa hàng để mua trang bị
Sau khi chọn vào cửa hàng thì sẽ xuất hiện giao diện của cửa hàng:
 
- Người chơi sẽ nhập tên trang bị mình muốn mua: ví dụ là Basic Armor
- Sau đó chọn nhân vật mình muốn trang bị và cuối cùng là xem chỉ số nhân vật sau khi trang bị trang bị đó
 
- Trong ví dụ người chơi chọn mua Basic Armor có chỉ số là +100DEF thì Tank sau khi trang bị vật phẩm sẽ tăng DEF từ 500->600
- Sau đó nếu muốn nâng cấp tiếp thì chọn 1 hăojc 0 để rời khỏi cửa hàng.
 
* Trận chiến
- Sau khi rời khỏi cửa hàng thì người chơi sẽ tiến hành chiến đấu với kẻ địch
 
- Lượt đầu tiên sẽ là của người chơi, người chơi sẽ cho lần lượt các nhân vật của mình là Tank, Warrior và Wizard tấn công kẻ địch được chọn. Người chơi có thể kích hoạt kĩ năng nếu muốn. Tuy nhiên kĩ năng chỉ được sử dụng duy nhất một lần trong mỗi màn. Nếu qua màn thì kĩ năng sẽ được reset
+ Lượt của Tank
 

+ Lượt của Warrior
 
+ Lượt của Wizard
 
- Sau khi người chơi kết thúc lượt sẽ đến quân địch. Quân địch mặc địch tấn công theo thứ tự Tank, Warrior rồi mới tới Wizard
 
- Sau đó tới lượt của người chơi và lặp lại đến khi nào toàn bộ kẻ địch bị tiêu diệt hoặc toàn bộ nhân vật của người chơi bị tiêu diệt.
+ Lượt người chơi
 
+ Lượt kẻ địch
 
+ Lượt người chơi
 
- Sau khi toàn bộ kẻ địch bị tiêu diệt thì người chơi sẽ chiến thắng
 
- Sau đó người chơi có thể tiếp tục chơi tiếp hoặc thoát khỏi trò chơi.
 
 
- Khi tiếp tục chap 2 người chơi sẽ được cấp thêm tiền sau khi đã giành chiến thắng và có thể vào cửa hàng để mua trang bị hoặc nâng cấp kĩ năng.
