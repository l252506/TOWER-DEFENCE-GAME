
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <cmath>
//#include <string>
//
//const int COLS = 20;
//const int ROWS = 15;
//const int UI_HEIGHT = 60;
//const int TILE_SIZE = 40;
//const int WIN_WIDTH = COLS * TILE_SIZE;           // 800
//const int WIN_HEIGHT = ROWS * TILE_SIZE + UI_HEIGHT; // 660
//
//const int MAX_WAYPOINTS = 20;
//const int MAX_ENEMIES = 100;
//const int MAX_TOWERS = 50;
//const int MAX_PROJECTILES = 300;
//const int MAX_WAVES = 5;
//const int MAX_SPAWN = 15;
//const int SHOP_ITEMS = 5;
//
//// each map cell stores one of these ints 
//const int TILE_GRASS = 0;
//const int TILE_PATH = 1;
//const int TILE_BLOCKED = 2;
//
//// one corner on the enemy walking route (pixel position)
//class Waypoint {
//public:
//    float x;
//    float y;
//};
//
//// little red/green bar above enemies so you see HP
//
//static void drawHpBar(sf::RenderWindow& window, float x, float y,
//    int hp, int maxHp, float width = 30.f)
//{
//    sf::RectangleShape bg({ width, 5.f });
//    bg.setFillColor(sf::Color::Red);
//    bg.setPosition(x - width / 2.f, y - 22.f);
//
//    float ratio = (float)hp / (float)maxHp; // 0..1 how much hp left
//    if (ratio < 0.f) ratio = 0.f;
//    sf::RectangleShape fg({ width * ratio, 5.f });
//    fg.setFillColor(sf::Color::Green);
//    fg.setPosition(x - width / 2.f, y - 22.f);
//
//    window.draw(bg);
//    window.draw(fg);
//}
//
//// parent class for anything that has a position + hp (enemy + tower inherit from this)
//class Entity {
//protected:
//    float x, y;
//    int   hp;
//    int   maxHp;
//
//public:
//    Entity(float x, float y, int hp)
//        : x(x), y(y), hp(hp), maxHp(hp) {
//    }
//
//    // = 0 means "pure virtual" — child class MUST implement these
//    virtual void update(float dt) = 0;
//    virtual void render(sf::RenderWindow& win) = 0;
//    virtual void takeDamage(int dmg) { hp -= dmg; }
//
//    bool  isAlive()  const { return hp > 0; }
//    float getX()     const { return x; }
//    float getY()     const { return y; }
//    int   getHp()    const { return hp; }
//    int   getMaxHp() const { return maxHp; }
//
//    // optional: compare two things by same x,y (was in spec for operator overloading)
//    bool operator==(const Entity& other) const {
//        return (x == other.x && y == other.y);
//    }
//
//    virtual ~Entity() {}
//};
//
//class Enemy : public Entity {
//protected:
//    float   speed;
//    float   originalSpeed;
//    int     reward;
//    int     waypointIndex;
//    bool    reached;
//    sf::Color color;
//    const Waypoint* path;
//    int            pathSize;
//
//public:
//    Enemy(float x, float y, int hp, float speed, int reward, sf::Color color)
//        : Entity(x, y, hp),
//        speed(speed), originalSpeed(speed), reward(reward),
//        waypointIndex(0), reached(false),
//        color(color), path(nullptr), pathSize(0) {
//    }
//
//    void setPath(const Waypoint* p, int size) {
//        path = p;
//        pathSize = size;
//    }
//
//    // walk along waypoints: steer toward next point, when close enough go to next
//    virtual void update(float dt) override {
//        if (!path || waypointIndex >= pathSize) {
//            reached = true;
//            return;
//        }
//
//        float tx = path[waypointIndex].x;
//        float ty = path[waypointIndex].y;
//        float dx = tx - x;
//        float dy = ty - y;
//        float dist = std::sqrt(dx * dx + dy * dy);
//
//        if (dist < 5.f) {
//            waypointIndex++;
//            if (waypointIndex >= pathSize)
//                reached = true;
//        }
//        else {
//            // (dx/dist, dy/dist) is unit direction; * speed * dt moves in pixels this frame
//            x += (dx / dist) * speed * dt;
//            y += (dy / dist) * speed * dt;
//        }
//    }
//
//    virtual void render(sf::RenderWindow& win) override {
//        sf::CircleShape shape(12.f);
//        shape.setFillColor(color);
//        shape.setOrigin(12.f, 12.f);
//        shape.setPosition(x, y);
//        win.draw(shape);
//        drawHpBar(win, x, y, hp, maxHp);
//    }
//
//    bool  hasReached() const { return reached; }
//    int   getReward()  const { return reward; }
//
//    void applySlowEffect(float amount) { speed = originalSpeed * (1.f - amount); }
//    void resetSpeed() { speed = originalSpeed; }
//
//    virtual ~Enemy() {}
//};
//
//// =====================================================
//// CONCRETE ENEMY 1: BasicEnemy
//// Average speed, average HP
//// =====================================================
//
//class BasicEnemy : public Enemy {
//public:
//    BasicEnemy(float x, float y)
//        : Enemy(x, y, 100, 80.f, 10, sf::Color::Red) {
//    }
//
//    void render(sf::RenderWindow& win) override {
//        sf::CircleShape shape(12.f);
//        shape.setFillColor(color);
//        shape.setOrigin(12.f, 12.f);
//        shape.setPosition(x, y);
//        win.draw(shape);
//        drawHpBar(win, x, y, hp, maxHp);
//    }
//};
//
//// =====================================================
//// CONCRETE ENEMY 2: FastEnemy
//// Very fast, low HP, triangle shape
//// =====================================================
//
//class FastEnemy : public Enemy {
//public:
//    FastEnemy(float x, float y)
//        : Enemy(x, y, 50, 180.f, 15, sf::Color::Yellow) {
//    }
//
//    void render(sf::RenderWindow& win) override {
//        sf::CircleShape shape(10.f, 3); // 3 sides = triangle
//        shape.setFillColor(color);
//        shape.setOrigin(10.f, 10.f);
//        shape.setPosition(x, y);
//        win.draw(shape);
//        drawHpBar(win, x, y, hp, maxHp);
//    }
//};
//
//// =====================================================
//// CONCRETE ENEMY 3: TankEnemy
//// Very slow, very high HP, large square shape
//// =====================================================
//
//class TankEnemy : public Enemy {
//public:
//    TankEnemy(float x, float y)
//        : Enemy(x, y, 400, 40.f, 30, sf::Color(150, 0, 150)) {
//    }
//
//    void render(sf::RenderWindow& win) override {
//        sf::RectangleShape shape({ 26.f, 26.f });
//        shape.setFillColor(color);
//        shape.setOrigin(13.f, 13.f);
//        shape.setPosition(x, y);
//        win.draw(shape);
//        drawHpBar(win, x, y, hp, maxHp, 40.f);
//    }
//};
//
//// =====================================================
//// CONCRETE ENEMY 4: FlyingEnemy
//// Ignores the path, flies straight to the exit
//// =====================================================
//
//class FlyingEnemy : public Enemy {
//public:
//    FlyingEnemy(float x, float y)
//        : Enemy(x, y, 80, 120.f, 20, sf::Color::Cyan) {
//    }
//
//    // doesn't follow every corner — goes straight to the last waypoint (the "exit")
//    void update(float dt) override {
//        if (!path || pathSize == 0) { reached = true; return; }
//
//        float tx = path[pathSize - 1].x;
//        float ty = path[pathSize - 1].y;
//        float dx = tx - x;
//        float dy = ty - y;
//        float dist = std::sqrt(dx * dx + dy * dy);
//
//        if (dist < 5.f) {
//            reached = true;
//        }
//        else {
//            x += (dx / dist) * speed * dt;
//            y += (dy / dist) * speed * dt;
//        }
//    }
//
//    void render(sf::RenderWindow& win) override {
//        sf::CircleShape shape(10.f, 6); // hexagon
//        shape.setFillColor(color);
//        shape.setOrigin(10.f, 10.f);
//        shape.setPosition(x, y);
//
//        sf::CircleShape dot(3.f);
//        dot.setFillColor(sf::Color::White);
//        dot.setOrigin(3.f, 3.f);
//        dot.setPosition(x, y);
//
//        win.draw(shape);
//        win.draw(dot);
//        drawHpBar(win, x, y, hp, maxHp);
//    }
//};
//
//// =====================================================
//// CONCRETE ENEMY 5: HealerEnemy (custom)
//// Heals itself 10 HP every 2 seconds
//// =====================================================
//
//class HealerEnemy : public Enemy {
//private:
//    float healTimer;
//public:
//    HealerEnemy(float x, float y)
//        : Enemy(x, y, 150, 70.f, 25, sf::Color(0, 200, 0)), healTimer(0.f) {
//    }
//
//    void update(float dt) override {
//        Enemy::update(dt); // normal movement
//
//        healTimer += dt;
//        if (healTimer >= 2.0f) {
//            hp += 10;
//            if (hp > maxHp) hp = maxHp;
//            healTimer = 0.f;
//        }
//    }
//
//    void render(sf::RenderWindow& win) override {
//        sf::CircleShape shape(12.f);
//        shape.setFillColor(color);
//        shape.setOrigin(12.f, 12.f);
//        shape.setPosition(x, y);
//
//        // White cross symbol on top
//        sf::RectangleShape hBar({ 14.f, 4.f });
//        hBar.setFillColor(sf::Color::White);
//        hBar.setOrigin(7.f, 2.f);
//        hBar.setPosition(x, y);
//
//        sf::RectangleShape vBar({ 4.f, 14.f });
//        vBar.setFillColor(sf::Color::White);
//        vBar.setOrigin(2.f, 7.f);
//        vBar.setPosition(x, y);
//
//        win.draw(shape);
//        win.draw(hBar);
//        win.draw(vBar);
//        drawHpBar(win, x, y, hp, maxHp);
//    }
//};
//
//// bullet flying toward a point (usually where an enemy was when we fired)
//class Projectile {
//private:
//    float     x, y;
//    float     targetX, targetY;
//    float     speed;
//    int       damage;
//    bool      active;
//    sf::Color color;
//    float     slowAmount; // 0 = no slow, 0.5 = 50% slower
//
//public:
//    Projectile()
//        : x(0), y(0), targetX(0), targetY(0),
//        speed(0), damage(0), active(false),
//        color(sf::Color::White), slowAmount(0.f) {
//    }
//
//    Projectile(float x, float y, float tx, float ty,
//        float speed, int damage, sf::Color color, float slow = 0.f)
//        : x(x), y(y), targetX(tx), targetY(ty),
//        speed(speed), damage(damage),
//        active(true), color(color), slowAmount(slow) {
//    }
//
//    void update(float dt) {
//        float dx = targetX - x;
//        float dy = targetY - y;
//        float dist = std::sqrt(dx * dx + dy * dy);
//
//        if (dist < 8.f) {
//            active = false; // arrived (we don't track homing in this simple version)
//            return;
//        }
//
//        x += (dx / dist) * speed * dt;
//        y += (dy / dist) * speed * dt;
//    }
//
//    void render(sf::RenderWindow& win) {
//        sf::CircleShape shape(4.f);
//        shape.setFillColor(color);
//        shape.setOrigin(4.f, 4.f);
//        shape.setPosition(x, y);
//        win.draw(shape);
//    }
//
//    bool  isActive()      const { return active; }
//    int   getDamage()     const { return damage; }
//    float getSlowAmount() const { return slowAmount; }
//    float getX()          const { return x; }
//    float getY()          const { return y; }
//    void  deactivate() { active = false; }
//};
//
//// tower base: big hp number so towers basically never die in this game
//class Tower : public Entity {
//protected:
//    float     range;
//    float     fireRate;
//    float     fireCooldown;
//    int       damage;
//    int       cost;
//    sf::Color color;
//
//public:
//    Tower(float x, float y, float range, float fireRate,
//        int damage, int cost, sf::Color color)
//        : Entity(x, y, 9999), // towers don't really lose hp here
//        range(range), fireRate(fireRate), fireCooldown(0.f),
//        damage(damage), cost(cost), color(color) {
//    }
//
//    // Countdown fire cooldown each frame
//    virtual void update(float dt) override {
//        if (fireCooldown > 0.f) fireCooldown -= dt;
//    }
//
//    // child classes implement what "shooting" means for that tower type
//    virtual void attack(Enemy* enemies[], int enemyCount,
//        Projectile projectiles[], int& projCount) = 0;
//
//    virtual void render(sf::RenderWindow& win) override {
//        sf::RectangleShape shape({ 32.f, 32.f });
//        shape.setFillColor(color);
//        shape.setOrigin(16.f, 16.f);
//        shape.setPosition(x, y);
//        win.draw(shape);
//    }
//
//    // Towers cannot be damaged
//    void takeDamage(int) override {}
//
//    // Draw transparent range circle
//    void drawRangeCircle(sf::RenderWindow& win) {
//        sf::CircleShape circle(range);
//        circle.setFillColor(sf::Color(255, 255, 255, 20));
//        circle.setOutlineColor(sf::Color(255, 255, 255, 80));
//        circle.setOutlineThickness(1.f);
//        circle.setOrigin(range, range);
//        circle.setPosition(x, y);
//        win.draw(circle);
//    }
//
//    // Find the nearest enemy within range
//    Enemy* findClosestEnemy(Enemy* enemies[], int enemyCount) {
//        Enemy* closest = nullptr;
//        float  minDist = range + 1.f;
//
//        for (int i = 0; i < enemyCount; i++) {
//            if (!enemies[i] || !enemies[i]->isAlive()) continue;
//            float dx = enemies[i]->getX() - x;
//            float dy = enemies[i]->getY() - y;
//            float d = std::sqrt(dx * dx + dy * dy);
//            if (d <= range && d < minDist) {
//                minDist = d;
//                closest = enemies[i];
//            }
//        }
//        return closest;
//    }
//
//    int   getCost()  const { return cost; }
//    float getRange() const { return range; }
//
//    virtual ~Tower() {}
//};
//
//// =====================================================
//// CONCRETE TOWER 1: CannonTower
//// High damage, slow fire rate
//// =====================================================
//
//class CannonTower : public Tower {
//private:
//    sf::SoundBuffer fireBuffer;
//    sf::Sound fireSound;
//
//public:
//    CannonTower(float x, float y)
//        : Tower(x, y, 120.f, 0.8f, 80, 100, sf::Color(180, 90, 0))
//    {
//        fireBuffer.loadFromFile("assets/sounds/cannon.wav");
//        fireSound.setBuffer(fireBuffer);
//    }
//
//    void attack(Enemy* enemies[], int enemyCount,
//        Projectile projectiles[], int& projCount) override
//    {
//        if (fireCooldown > 0.f) return;
//
//        Enemy* target = findClosestEnemy(enemies, enemyCount);
//        if (!target) return;
//
//        if (projCount < MAX_PROJECTILES)
//        {
//            projectiles[projCount++] = Projectile(
//                x, y,
//                target->getX(), target->getY(),
//                300.f,
//                damage,
//                sf::Color(255, 140, 0)
//            );
//
//            fireSound.play();
//        }
//
//        fireCooldown = 1.f / fireRate;
//    }
//
//    void render(sf::RenderWindow& win) override
//    {
//        sf::CircleShape base(16.f);
//        base.setFillColor(color);
//        base.setOrigin(16.f, 16.f);
//        base.setPosition(x, y);
//
//        sf::RectangleShape barrel({ 20.f, 6.f });
//        barrel.setFillColor(sf::Color(100, 50, 0));
//        barrel.setOrigin(0.f, 3.f);
//        barrel.setPosition(x, y);
//
//        win.draw(base);
//        win.draw(barrel);
//    }
//};
//// =====================================================
//// CONCRETE TOWER 2: SniperTower
//// Very long range, single target
//// =====================================================
//
//class SniperTower : public Tower {
//private:
//    sf::SoundBuffer fireBuffer;
//    sf::Sound fireSound;
//
//public:
//    SniperTower(float x, float y)
//        : Tower(x, y, 250.f, 0.5f, 120, 150, sf::Color(0, 0, 200))
//    {
//        fireBuffer.loadFromFile("assets/sounds/sniper.wav");
//        fireSound.setBuffer(fireBuffer);
//    }
//
//    void attack(Enemy* enemies[], int enemyCount,
//        Projectile projectiles[], int& projCount) override
//    {
//        if (fireCooldown > 0.f) return;
//
//        Enemy* target = findClosestEnemy(enemies, enemyCount);
//        if (!target) return;
//
//        if (projCount < MAX_PROJECTILES)
//        {
//            projectiles[projCount++] = Projectile(
//                x, y,
//                target->getX(), target->getY(),
//                600.f,
//                damage,
//                sf::Color(0, 100, 255)
//            );
//
//            fireSound.play();
//        }
//
//        fireCooldown = 1.f / fireRate;
//    }
//
//    void render(sf::RenderWindow& win) override
//    {
//        sf::CircleShape base(14.f, 8);
//        base.setFillColor(color);
//        base.setOrigin(14.f, 14.f);
//        base.setPosition(x, y);
//
//        sf::RectangleShape barrel({ 26.f, 4.f });
//        barrel.setFillColor(sf::Color(0, 0, 100));
//        barrel.setOrigin(0.f, 2.f);
//        barrel.setPosition(x, y);
//
//        win.draw(base);
//        win.draw(barrel);
//    }
//};
//// =====================================================
//// CONCRETE TOWER 3: MachineGunTower
//// Fast fire rate, low damage per bullet
//// =====================================================
//
//class MachineGunTower : public Tower {
//private:
//    sf::SoundBuffer fireBuffer;
//    sf::Sound fireSound;
//
//public:
//    MachineGunTower(float x, float y)
//        : Tower(x, y, 100.f, 5.f, 15, 120, sf::Color(80, 80, 80))
//    {
//        fireBuffer.loadFromFile("assets/sounds/machinegun.wav");
//        fireSound.setBuffer(fireBuffer);
//    }
//
//    void attack(Enemy* enemies[], int enemyCount,
//        Projectile projectiles[], int& projCount) override
//    {
//        if (fireCooldown > 0.f) return;
//
//        Enemy* target = findClosestEnemy(enemies, enemyCount);
//        if (!target) return;
//
//        if (projCount < MAX_PROJECTILES)
//        {
//            projectiles[projCount++] = Projectile(
//                x, y,
//                target->getX(), target->getY(),
//                500.f,
//                damage,
//                sf::Color(200, 200, 200)
//            );
//
//            fireSound.play();
//        }
//
//        fireCooldown = 1.f / fireRate;
//    }
//
//    void render(sf::RenderWindow& win) override
//    {
//        sf::RectangleShape base({ 28.f, 28.f });
//        base.setFillColor(color);
//        base.setOrigin(14.f, 14.f);
//        base.setPosition(x, y);
//
//        sf::RectangleShape barrel({ 22.f, 5.f });
//        barrel.setFillColor(sf::Color(50, 50, 50));
//        barrel.setOrigin(0.f, 2.5f);
//        barrel.setPosition(x, y);
//
//        win.draw(base);
//        win.draw(barrel);
//    }
//};
//// =====================================================
//// CONCRETE TOWER 4: SlowTower
//// Slows enemies down on hit
//// =====================================================
//
//class SlowTower : public Tower {
//private:
//    sf::SoundBuffer fireBuffer;
//    sf::Sound fireSound;
//
//public:
//    SlowTower(float x, float y)
//        : Tower(x, y, 110.f, 1.5f, 5, 90, sf::Color(0, 200, 200))
//    {
//        fireBuffer.loadFromFile("assets/sounds/slow.wav");
//        fireSound.setBuffer(fireBuffer);
//    }
//
//    void attack(Enemy* enemies[], int enemyCount,
//        Projectile projectiles[], int& projCount) override
//    {
//        if (fireCooldown > 0.f) return;
//
//        Enemy* target = findClosestEnemy(enemies, enemyCount);
//        if (!target) return;
//
//        if (projCount < MAX_PROJECTILES)
//        {
//            projectiles[projCount++] = Projectile(
//                x, y,
//                target->getX(), target->getY(),
//                250.f,
//                damage,
//                sf::Color(0, 255, 255),
//                0.5f
//            );
//
//            fireSound.play();
//        }
//
//        fireCooldown = 1.f / fireRate;
//    }
//
//    void render(sf::RenderWindow& win) override
//    {
//        sf::CircleShape base(15.f, 6);
//        base.setFillColor(color);
//        base.setOrigin(15.f, 15.f);
//        base.setPosition(x, y);
//
//        win.draw(base);
//    }
//};
//// =====================================================
//// CONCRETE TOWER 5: BombTower (custom)
//// Damages ALL enemies near the impact point
//// =====================================================
//
//class BombTower : public Tower {
//private:
//    sf::SoundBuffer fireBuffer;
//    sf::Sound fireSound;
//
//public:
//    BombTower(float x, float y)
//        : Tower(x, y, 130.f, 0.6f, 60, 175, sf::Color(220, 50, 50))
//    {
//        fireBuffer.loadFromFile("assets/sounds/bomb.wav");
//        fireSound.setBuffer(fireBuffer);
//    }
//
//    void attack(Enemy* enemies[], int enemyCount,
//        Projectile projectiles[], int& projCount) override
//    {
//        if (fireCooldown > 0.f) return;
//
//        Enemy* target = findClosestEnemy(enemies, enemyCount);
//        if (!target) return;
//
//        if (projCount < MAX_PROJECTILES)
//        {
//            projectiles[projCount++] = Projectile(
//                x, y,
//                target->getX(), target->getY(),
//                280.f,
//                damage,
//                sf::Color(255, 80, 0)
//            );
//
//            fireSound.play();
//        }
//
//        fireCooldown = 1.f / fireRate;
//    }
//
//    void render(sf::RenderWindow& win) override
//    {
//        sf::CircleShape base(16.f);
//        base.setFillColor(color);
//        base.setOrigin(16.f, 16.f);
//        base.setPosition(x, y);
//
//        sf::CircleShape top(6.f);
//        top.setFillColor(sf::Color(255, 200, 0));
//        top.setOrigin(6.f, 6.f);
//        top.setPosition(x, y - 10.f);
//
//        win.draw(base);
//        win.draw(top);
//    }
//};
//
//// one wave: which enemies spawn + how many + delay between spawns
//class Wave {
//public:
//    int enemyTypes[MAX_SPAWN]; // 0 basic, 1 fast, 2 tank, 3 flying, 4 healer
//    int count;
//    float spawnDelay;
//
//    Wave() {
//        count = 0;
//        spawnDelay = 1.f;
//        for (int i = 0; i < MAX_SPAWN; i++)
//            enemyTypes[i] = 0;
//    }
//};
//
//class Game {
//private:
//    sf::RenderWindow window;
//    sf::Font         font;
//    bool             fontLoaded;
//
//    // grid[r][c] holds TILE_GRASS, TILE_PATH, or TILE_BLOCKED
//    int grid[ROWS][COLS];
//    Waypoint waypoints[MAX_WAYPOINTS];
//    int      waypointCount;
//
//    Enemy* enemies[MAX_ENEMIES];
//    int    enemyCount;
//
//    Tower* towers[MAX_TOWERS];
//    int    towerCount;
//
//    Projectile projectiles[MAX_PROJECTILES];
//    int        projCount;
//
//    Wave  waves[MAX_WAVES];
//    int   currentWave;      // 0..MAX_WAVES-1 while playing
//    int   spawnIndex;       // which enemy in this wave we are spawning next
//    float spawnTimer;       // countdown between spawns
//    bool  waveActive;       // true while enemies still spawning / alive this wave
//    float wavePauseTimer;   // wait time before next wave starts
//
//    int gold;
//    int lives;
//    int score;
//
//    bool gameOver;
//    bool gameWon;
//
//    int         selectedTower; // index in shop, or -1 = none
//    int         shopCosts[SHOP_ITEMS];
//    sf::Color   shopColors[SHOP_ITEMS];
//    std::string shopNames[SHOP_ITEMS];
//
//    // ── Setup ─────────────────────────────────────
//
//    void setupMap() {
//        // start everything as buildable grass
//        for (int r = 0; r < ROWS; r++)
//            for (int c = 0; c < COLS; c++)
//                grid[r][c] = TILE_GRASS;
//
//        // path tiles (brown in drawMap)
//        for (int c = 0; c <= 17; c++) grid[2][c] = TILE_PATH;
//        for (int r = 2; r <= 7; r++) grid[r][17] = TILE_PATH;
//        for (int c = 2; c <= 17; c++) grid[7][c] = TILE_PATH;
//        for (int r = 7; r <= 12; r++) grid[r][2] = TILE_PATH;
//        for (int c = 2; c <= 19; c++) grid[12][c] = TILE_PATH;
//
//        // waypoints = center of each path corner, in walking order
//        waypoints[0].x = 0 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[0].y = 2 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[1].x = 17 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[1].y = 2 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[2].x = 17 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[2].y = 7 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[3].x = 2 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[3].y = 7 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[4].x = 2 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[4].y = 12 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[5].x = 19 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypoints[5].y = 12 * TILE_SIZE + TILE_SIZE / 2.f;
//        waypointCount = 6;
//    }
//
//    void setupWaves() {
//        // Wave 1: 8 basic
//        waves[0].count = 8; waves[0].spawnDelay = 1.5f;
//        for (int i = 0; i < 8; i++) waves[0].enemyTypes[i] = 0;
//
//        // Wave 2: 6 basic + 4 fast
//        waves[1].count = 10; waves[1].spawnDelay = 1.2f;
//        for (int i = 0; i < 6; i++) waves[1].enemyTypes[i] = 0;
//        for (int i = 6; i < 10; i++) waves[1].enemyTypes[i] = 1;
//
//        // Wave 3: 5 basic + 3 fast + 2 tank
//        waves[2].count = 10; waves[2].spawnDelay = 1.0f;
//        for (int i = 0; i < 5; i++) waves[2].enemyTypes[i] = 0;
//        for (int i = 5; i < 8; i++) waves[2].enemyTypes[i] = 1;
//        for (int i = 8; i < 10; i++) waves[2].enemyTypes[i] = 2;
//
//        // Wave 4: mixed with flying and healer
//        waves[3].count = 12; waves[3].spawnDelay = 0.9f;
//        for (int i = 0; i < 4; i++) waves[3].enemyTypes[i] = 0;
//        for (int i = 4; i < 7; i++) waves[3].enemyTypes[i] = 1;
//        for (int i = 7; i < 9; i++) waves[3].enemyTypes[i] = 2;
//        for (int i = 9; i < 11; i++) waves[3].enemyTypes[i] = 3;
//        waves[3].enemyTypes[11] = 4;
//
//        // Wave 5: hardest
//        waves[4].count = 15; waves[4].spawnDelay = 0.7f;
//        for (int i = 0; i < 3; i++) waves[4].enemyTypes[i] = 0;
//        for (int i = 3; i < 6; i++) waves[4].enemyTypes[i] = 1;
//        for (int i = 6; i < 10; i++) waves[4].enemyTypes[i] = 2;
//        for (int i = 10; i < 13; i++) waves[4].enemyTypes[i] = 3;
//        for (int i = 13; i < 15; i++) waves[4].enemyTypes[i] = 4;
//    }
//
//    void setupShop() {
//        shopCosts[0] = 100;  shopColors[0] = sf::Color(180, 90, 0);  shopNames[0] = "Cannon $100";
//        shopCosts[1] = 150;  shopColors[1] = sf::Color(0, 0, 200);   shopNames[1] = "Sniper $150";
//        shopCosts[2] = 120;  shopColors[2] = sf::Color(80, 80, 80);  shopNames[2] = "MachGun $120";
//        shopCosts[3] = 90;   shopColors[3] = sf::Color(0, 200, 200); shopNames[3] = "Slow $90";
//        shopCosts[4] = 175;  shopColors[4] = sf::Color(220, 50, 50); shopNames[4] = "Bomb $175";
//    }
//
//    // ── Spawning ──────────────────────────────────
//
//    // type: 0 basic, 1 fast, 2 tank, 3 flying, 4 healer (same numbers as setupWaves)
//    void spawnEnemy(int type) {
//        if (enemyCount >= MAX_ENEMIES) return;
//
//        float sx = waypoints[0].x;
//        float sy = waypoints[0].y;
//
//        Enemy* e = nullptr;
//        switch (type) {
//        case 0: e = new BasicEnemy(sx, sy);  break;
//        case 1: e = new FastEnemy(sx, sy);   break;
//        case 2: e = new TankEnemy(sx, sy);   break;
//        case 3: e = new FlyingEnemy(sx, sy); break;
//        case 4: e = new HealerEnemy(sx, sy); break;
//        }
//        if (e) {
//            e->setPath(waypoints, waypointCount);
//            enemies[enemyCount++] = e;
//        }
//    }
//
//    // ── Tower placement ───────────────────────────
//
//    bool isTileAvailable(int tx, int ty) {
//        if (tx < 0 || tx >= COLS || ty < 0 || ty >= ROWS) return false;
//        return grid[ty][tx] == TILE_GRASS;
//    }
//
//    void placeTower(int tileX, int tileY) {
//        if (!isTileAvailable(tileX, tileY))         return;
//        if (gold < shopCosts[selectedTower])         return;
//        if (towerCount >= MAX_TOWERS)                return;
//
//        float px = tileX * TILE_SIZE + TILE_SIZE / 2.f;
//        float py = tileY * TILE_SIZE + TILE_SIZE / 2.f;
//
//        Tower* t = nullptr;
//        switch (selectedTower) {
//        case 0: t = new CannonTower(px, py);     break;
//        case 1: t = new SniperTower(px, py);     break;
//        case 2: t = new MachineGunTower(px, py); break;
//        case 3: t = new SlowTower(px, py);       break;
//        case 4: t = new BombTower(px, py);       break;
//        }
//        if (t) {
//            towers[towerCount++] = t;
//            gold -= shopCosts[selectedTower];
//            grid[tileY][tileX] = TILE_BLOCKED;
//        }
//    }
//
//    // ── Collision detection ───────────────────────
//
//    void checkCollisions() {
//        for (int p = 0; p < projCount; p++) {
//            if (!projectiles[p].isActive()) continue;
//
//            for (int e = 0; e < enemyCount; e++) {
//                if (!enemies[e] || !enemies[e]->isAlive()) continue;
//
//                float dx = projectiles[p].getX() - enemies[e]->getX();
//                float dy = projectiles[p].getY() - enemies[e]->getY();
//                float dist = std::sqrt(dx * dx + dy * dy);
//
//                if (dist < 15.f) {
//                    enemies[e]->takeDamage(projectiles[p].getDamage());
//
//                    if (projectiles[p].getSlowAmount() > 0.f)
//                        enemies[e]->applySlowEffect(projectiles[p].getSlowAmount());
//
//                    // only pay out when hp hits 0 (not every bullet hit)
//                    if (!enemies[e]->isAlive()) {
//                        gold += enemies[e]->getReward();
//                        score += enemies[e]->getReward();
//                    }
//
//                    projectiles[p].deactivate();
//                    break;
//                }
//            }
//        }
//    }
//
//    // ── Cleanup arrays ────────────────────────────
//
//    // compact the pointer array so we don't leave holes (nullptr gaps) in the middle
//    void removeDeadEnemies() {
//        int newCount = 0;
//        for (int i = 0; i < enemyCount; i++) {
//            if (enemies[i] && enemies[i]->isAlive()) {
//                enemies[newCount++] = enemies[i];
//            }
//            else {
//                delete enemies[i];
//                enemies[i] = nullptr;
//            }
//        }
//        enemyCount = newCount;
//    }
//
//    void removeInactiveProjectiles() {
//        int newCount = 0;
//        for (int i = 0; i < projCount; i++)
//            if (projectiles[i].isActive())
//                projectiles[newCount++] = projectiles[i];
//        projCount = newCount;
//    }
//
//    // ── Drawing ───────────────────────────────────
//
//    void drawMap() {
//        for (int r = 0; r < ROWS; r++) {
//            for (int c = 0; c < COLS; c++) {
//                sf::RectangleShape tile({ (float)TILE_SIZE - 1, (float)TILE_SIZE - 1 });
//                tile.setPosition((float)c * TILE_SIZE, (float)r * TILE_SIZE);
//
//                if (grid[r][c] == TILE_PATH)    tile.setFillColor(sf::Color(180, 140, 80));
//                else if (grid[r][c] == TILE_BLOCKED) tile.setFillColor(sf::Color(60, 80, 60));
//                else                            tile.setFillColor(sf::Color(60, 100, 60));
//
//                window.draw(tile);
//            }
//        }
//
//        // Highlight hovered tile while placing
//        if (selectedTower >= 0) {
//            sf::Vector2i mp = sf::Mouse::getPosition(window);
//            int tx = mp.x / TILE_SIZE;
//            int ty = mp.y / TILE_SIZE;
//            if (tx >= 0 && tx < COLS && ty >= 0 && ty < ROWS) {
//                sf::RectangleShape hl({ (float)TILE_SIZE - 1, (float)TILE_SIZE - 1 });
//                hl.setPosition((float)tx * TILE_SIZE, (float)ty * TILE_SIZE);
//                bool ok = (grid[ty][tx] == TILE_GRASS) && (gold >= shopCosts[selectedTower]);
//                hl.setFillColor(ok ? sf::Color(255, 255, 255, 60) : sf::Color(255, 0, 0, 60));
//                window.draw(hl);
//            }
//        }
//    }
//
//    void drawText(const std::string& str, float x, float y,
//        int size = 16, sf::Color col = sf::Color::White)
//    {
//        if (!fontLoaded) return;
//        sf::Text t;
//        t.setFont(font);
//        t.setString(str);
//        t.setCharacterSize(size);
//        t.setFillColor(col);
//        t.setPosition(x, y);
//        window.draw(t);
//    }
//
//    void drawUI() {
//        // Dark bottom bar
//        sf::RectangleShape bar({ (float)WIN_WIDTH, (float)UI_HEIGHT });
//        bar.setFillColor(sf::Color(20, 20, 20));
//        bar.setPosition(0.f, (float)(ROWS * TILE_SIZE));
//        window.draw(bar);
//
//        // Shop buttons
//        float btnW = WIN_WIDTH / (float)SHOP_ITEMS;
//        for (int i = 0; i < SHOP_ITEMS; i++) {
//            sf::Color col = shopColors[i];
//            if (i == selectedTower)      col = sf::Color(255, 255, 100);
//            if (gold < shopCosts[i])     col = sf::Color(col.r / 2, col.g / 2, col.b / 2);
//
//            sf::RectangleShape btn({ btnW - 4.f, 50.f });
//            btn.setPosition(i * btnW + 2.f, ROWS * TILE_SIZE + 5.f);
//            btn.setFillColor(col);
//            window.draw(btn);
//
//            drawText(shopNames[i], i * btnW + 5.f, ROWS * TILE_SIZE + 18.f, 11);
//        }
//
//        // Stats at the top
//        drawText("Score: " + std::to_string(score), 10.f, 5.f, 16, sf::Color(245, 200, 66));
//        drawText("Gold: " + std::to_string(gold), 170.f, 5.f, 16, sf::Color(230, 168, 37));
//        drawText("Lives: " + std::to_string(lives), 310.f, 5.f);
//        drawText("Wave: " + std::to_string(currentWave) + "/" + std::to_string(MAX_WAVES), 430.f, 5.f);
//
//        if (!waveActive && currentWave < MAX_WAVES)
//            drawText("Next wave in: " + std::to_string((int)wavePauseTimer + 1), 460.f, 5.f);
//
//        if (waveActive)
//            drawText("Wave in progress!", 460.f, 5.f, 16, sf::Color::Yellow);
//    }
//
//    void drawGameOver() {
//        window.clear(sf::Color(20, 0, 0));
//        drawText("GAME OVER", WIN_WIDTH / 2.f - 160.f, WIN_HEIGHT / 2.f - 80.f, 60, sf::Color::Red);
//        drawText("Final Score: " + std::to_string(score),
//            WIN_WIDTH / 2.f - 100.f, WIN_HEIGHT / 2.f + 10.f, 24);
//        drawText("You reached Wave " + std::to_string(currentWave),
//            WIN_WIDTH / 2.f - 130.f, WIN_HEIGHT / 2.f + 20.f, 24);
//        drawText("Close the window to exit.",
//            WIN_WIDTH / 2.f - 140.f, WIN_HEIGHT / 2.f + 60.f, 24);
//    }
//
//    void drawWin() {
//        window.clear(sf::Color(0, 20, 0));
//        drawText("YOU WIN!", WIN_WIDTH / 2.f - 150.f, WIN_HEIGHT / 2.f - 80.f, 60, sf::Color::Green);
//        drawText("All waves defeated!  Gold: " + std::to_string(gold),
//            WIN_WIDTH / 2.f - 200.f, WIN_HEIGHT / 2.f + 20.f, 24);
//        drawText("Final Score: " + std::to_string(score),
//            WIN_WIDTH / 2.f - 100.f, WIN_HEIGHT / 2.f + 10.f, 24);
//        drawText("Close the window to exit.",
//            WIN_WIDTH / 2.f - 140.f, WIN_HEIGHT / 2.f + 60.f, 24);
//    }
//
//public:
//
//    // ── Constructor ───────────────────────────────
//
//    Game()
//        : window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Tower Defense - OOP Project"),
//        fontLoaded(false),
//        enemyCount(0), towerCount(0), projCount(0),
//        currentWave(0), spawnIndex(0), spawnTimer(0.f),
//        waveActive(false), wavePauseTimer(3.f),
//        gold(150), lives(20), score(0),
//        gameOver(false), gameWon(false),
//        selectedTower(-1), waypointCount(0)
//    {
//        window.setFramerateLimit(60);
//
//        // Try to load font (put arial.ttf in assets/fonts/)
//        if (font.loadFromFile("assets/fonts/arial.ttf"))
//            fontLoaded = true;
//
//        // Clear all arrays to nullptr
//        for (int i = 0; i < MAX_ENEMIES; i++) enemies[i] = nullptr;
//        for (int i = 0; i < MAX_TOWERS; i++) towers[i] = nullptr;
//
//        setupMap();
//        setupWaves();
//        setupShop();
//    }
//
//    // ── Destructor: free all heap memory ──────────
//
//    ~Game() {
//        for (int i = 0; i < MAX_ENEMIES; i++) { delete enemies[i]; enemies[i] = nullptr; }
//        for (int i = 0; i < MAX_TOWERS; i++) { delete towers[i];  towers[i] = nullptr; }
//    }
//
//    // ── Main loop ─────────────────────────────────
//
//    void run() {
//        sf::Clock clock;
//
//        while (window.isOpen()) {
//
//            // dt = time since last frame in seconds (used for movement "per second")
//            float dt = clock.restart().asSeconds();
//            if (dt > 0.05f) dt = 0.05f; // if lag spike, don't skip too far ahead in one step
//
//            // ── Events ──────────────────────────
//            sf::Event event;
//            while (window.pollEvent(event)) {
//
//                if (event.type == sf::Event::Closed)
//                    window.close();
//
//                if (event.type == sf::Event::KeyPressed)
//                    if (event.key.code == sf::Keyboard::Escape)
//                        selectedTower = -1;
//
//                if (event.type == sf::Event::MouseButtonPressed &&
//                    event.mouseButton.button == sf::Mouse::Left)
//                {
//                    int mx = event.mouseButton.x;
//                    int my = event.mouseButton.y;
//
//                    // Bottom bar: shop click
//                    if (my >= ROWS * TILE_SIZE) {
//                        float btnW = WIN_WIDTH / (float)SHOP_ITEMS;
//                        int   btn = (int)(mx / btnW);
//                        if (btn >= 0 && btn < SHOP_ITEMS)
//                            selectedTower = (selectedTower == btn) ? -1 : btn;
//                    }
//                    // Map click: place tower
//                    else if (selectedTower >= 0) {
//                        placeTower(mx / TILE_SIZE, my / TILE_SIZE);
//                    }
//                }
//            }
//
//            // ── Update ──────────────────────────
//            if (!gameOver && !gameWon) {
//
//                // Wave management
//                if (!waveActive) {
//                    wavePauseTimer -= dt;
//                    if (wavePauseTimer <= 0.f && currentWave < MAX_WAVES) {
//                        waveActive = true;
//                        spawnIndex = 0;
//                        spawnTimer = 0.f;
//                    }
//                    if (currentWave >= MAX_WAVES && enemyCount == 0)
//                        gameWon = true;
//                }
//
//                if (waveActive) {
//                    spawnTimer -= dt;
//                    if (spawnTimer <= 0.f && spawnIndex < waves[currentWave].count) {
//                        spawnEnemy(waves[currentWave].enemyTypes[spawnIndex]);
//                        spawnIndex++;
//                        spawnTimer = waves[currentWave].spawnDelay;
//                    }
//                    if (spawnIndex >= waves[currentWave].count && enemyCount == 0) {
//                        waveActive = false;
//                        currentWave++;
//                        // small reward between waves (gets bigger on later waves)
//                        int bonus = currentWave * 50;
//                        score += bonus;
//                        gold += bonus;
//                        wavePauseTimer = 4.f;
//                    }
//                }
//
//                // Update enemies
//                for (int i = 0; i < enemyCount; i++) {
//                    if (!enemies[i]) continue;
//                    enemies[i]->update(dt);
//                    if (enemies[i]->hasReached()) {
//                        lives--;
//                        delete enemies[i];
//                        enemies[i] = nullptr;
//                    }
//                }
//
//                // Update towers + fire
//                for (int i = 0; i < towerCount; i++) {
//                    if (!towers[i]) continue;
//                    towers[i]->update(dt);
//                    towers[i]->attack(enemies, enemyCount, projectiles, projCount);
//                }
//
//                // Update projectiles
//                for (int i = 0; i < projCount; i++)
//                    projectiles[i].update(dt);
//
//                checkCollisions();
//                removeDeadEnemies();
//                removeInactiveProjectiles();
//
//                if (lives <= 0) gameOver = true;
//            }
//
//            // ── Render ──────────────────────────
//            window.clear(sf::Color(30, 30, 30));
//
//            if (gameOver) { drawGameOver(); window.display(); continue; }
//            if (gameWon) { drawWin();      window.display(); continue; }
//
//            drawMap();
//
//            // Range preview circle follows mouse when tower selected
//            if (selectedTower >= 0) {
//                float ranges[] = { 120.f, 250.f, 100.f, 110.f, 130.f };
//                sf::Vector2i mp = sf::Mouse::getPosition(window);
//                sf::CircleShape rc(ranges[selectedTower]);
//                rc.setFillColor(sf::Color(255, 255, 255, 20));
//                rc.setOutlineColor(sf::Color(255, 255, 255, 80));
//                rc.setOutlineThickness(1.f);
//                rc.setOrigin(ranges[selectedTower], ranges[selectedTower]);
//                rc.setPosition((float)mp.x, (float)mp.y);
//                window.draw(rc);
//            }
//
//            for (int i = 0; i < towerCount; i++) if (towers[i])      towers[i]->render(window);
//            for (int i = 0; i < enemyCount; i++) if (enemies[i])     enemies[i]->render(window);
//            for (int i = 0; i < projCount; i++) if (projectiles[i].isActive()) projectiles[i].render(window);
//
//            drawUI();
//            window.display();
//        }
//    }
//};
//
//int main() {
//    Game game;
//    game.run();
//    return 0;
//}
