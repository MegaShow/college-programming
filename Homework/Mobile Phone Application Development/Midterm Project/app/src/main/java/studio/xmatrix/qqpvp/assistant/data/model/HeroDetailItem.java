package studio.xmatrix.qqpvp.assistant.data.model;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.util.ArrayList;
import java.util.List;

import io.objectbox.annotation.Convert;
import io.objectbox.annotation.Entity;
import io.objectbox.annotation.Id;
import io.objectbox.annotation.Index;
import io.objectbox.annotation.Unique;
import studio.xmatrix.qqpvp.assistant.data.common.converter.RelationListConverter;
import studio.xmatrix.qqpvp.assistant.data.common.converter.SkillListConverter;
import timber.log.Timber;

@Entity
public class HeroDetailItem {

    @Id
    long _id;

    @Unique
    @Index
    int id;

    String name;
    String type;
    int attrViability;
    int attrAttack;
    int attrSkill;
    int attrDifficulty;
    String skins;
    @Convert(converter = SkillListConverter.class, dbType = String.class)
    List<Skill> skills;
    int suggestFirstSkill;
    int suggestSecondSkill;
    String suggestSummoners;
    @Convert(converter = RelationListConverter.class, dbType = String.class)
    List<Relation> relations;
    String suggestFirstItems;
    String suggestFirstItemsDescription;
    String suggestSecondItems;
    String suggestSecondItemsDescription;
    String suggestInscriptions;
    String suggestInscriptionsDescription;
    String story;

    public HeroDetailItem() {

    }

    public String getType() {
        return type;
    }

    public String getSkins() {
        return skins;
    }

    public int getAttrViability() {
        return attrViability;
    }

    public int getAttrAttack() {
        return attrAttack;
    }

    public int getAttrSkill() {
        return attrSkill;
    }

    public int getAttrDifficulty() {
        return attrDifficulty;
    }

    public int getSuggestFirstSkill() {
        return suggestFirstSkill;
    }

    public int getSuggestSecondSkill() {
        return suggestSecondSkill;
    }

    public String getSuggestInscriptions() {
        return suggestInscriptions;
    }

    public String getSuggestInscriptionsDescription() {
        return suggestInscriptionsDescription;
    }

    public String getSuggestFirstItems() {
        return suggestFirstItems;
    }

    public String getSuggestFirstItemsDescription() {
        return suggestFirstItemsDescription;
    }

    public String getSuggestSecondItems() {
        return suggestSecondItems;
    }

    public String getSuggestSecondItemsDescription() {
        return suggestSecondItemsDescription;
    }

    public String getSuggestSummoners() {
        return suggestSummoners;
    }

    public List<Skill> getSkills() {
        return skills;
    }

    public HeroDetailItem(int id, Document document) {
        this.id = id;
        try {
            convertToName(document.select("h2.cover-name"));
            convertToType(document.select("span.herodetail-sort"));
            convertToAttrs(document.select("ul.cover-list > li"));
            convertToSkins(document.select("ul.pic-pf-list.pic-pf-list3"));
            convertToSkillList(document.select("div.skill-show > div.show-list"));
            convertToSuggestSkills(document.select(".sugg-skill > img"));
            convertToSuggestSummoners(document.select("p#skill3"));
            convertToHeroRelations(document.select(".hero-info.l.info"));
            convertToSuggestItems(document.select(".equip-bd > .equip-info"));
            convertToSuggestInscriptions(document.select("div.sugg-info.info"));
            convertToStory(document.select(".pop-story > .pop-bd > p"));
        } catch (IllegalArgumentException e) {
            Timber.e("Create HeroDetailItem failed.");
            e.printStackTrace();
        }
    }

    public String getStory() {
        return story;
    }

    public List<Relation> getRelations() {
        return relations;
    }

    public String getName() {
        return name;
    }

    public int getId() {
        return id;
    }

    public static class Skill {

        private String name;
        private String cd;
        private String consume;
        private String description;
        private String tips;

        Skill(String name, String cd, String consume, String description, String tips) {
            this.name = name;
            this.cd = cd;
            this.consume = consume;
            this.description = description;
            this.tips = tips;
        }

        public String getName() {
            return name;
        }

        public String getCd() {
            return cd;
        }

        public String getConsume() {
            return consume;
        }

        public String getDescription() {
            return description;
        }

        public String getTips() {
            return tips;
        }
    }

    public static class Relation {

        private int id;
        private int relation;
        private String description;

        Relation(int id, int relation, String description) {
            this.id = id;
            this.relation = relation;
            this.description = description;
        }

        public int getId() {
            return id;
        }

        // 最佳搭档
        public boolean isBestPartner() {
            return relation == 0;
        }

        // 压制英雄
        public boolean isLoser() {
            return relation == 1;
        }

        // 被压制英雄
        public boolean isWinner() {
            return relation == 2;
        }

        public String getDescription() {
            return description;
        }
    }

    private void convertToName(Elements select) throws IllegalArgumentException {
        if (select == null) {
            Timber.e("Convert to name fail, null pointer items");
            throw new IllegalArgumentException();
        }
        name = select.text();
    }

    private void convertToType(Elements select) throws IllegalArgumentException {
        if (select == null) {
            Timber.e("Convert to type fail, null pointer items");
            throw new IllegalArgumentException();
        }
        try {
            String typeStr = select.select("i").first().className();
            int typeInt = Integer.parseInt(typeStr.substring(typeStr.length() - 1));
            switch (typeInt) {
                case 1:
                    type = "战士";
                    break;
                case 2:
                    type = "法师";
                    break;
                case 3:
                    type = "坦克";
                    break;
                case 4:
                    type = "刺客";
                    break;
                case 5:
                    type = "射手";
                    break;
                case 6:
                    type = "辅助";
                    break;
            }
        } catch (NullPointerException e) {
            Timber.e("Convert to type fail, with element %s", select.html());
            throw new IllegalArgumentException(select.html());
        }
    }

    private void convertToAttrs(Elements select) throws IllegalArgumentException {
        if (select == null) {
            Timber.e("Convert to attrs fail, null pointer items");
            throw new IllegalArgumentException();
        }
        for (Element item : select) {
            try {
                String name = item.selectFirst("em").text();
                String style = item.selectFirst("i.ibar").attr("style");
                int value = Integer.parseInt(style.substring(6, style.indexOf('%')));
                switch (name) {
                    case "生存能力":
                        attrViability = value;
                        break;
                    case "攻击伤害":
                        attrAttack = value;
                        break;
                    case "技能效果":
                        attrSkill = value;
                        break;
                    case "上手难度":
                        attrDifficulty = value;
                        break;
                }
            } catch (NullPointerException e) {
                Timber.e("Convert to attr fail, with element %s", item.html());
                throw new IllegalArgumentException(item.html());
            }
        }
    }

    private void convertToSkins(Elements select) throws IllegalArgumentException {
        if (select == null) {
            Timber.e("Convert to skins fail, null pointer items");
            throw new IllegalArgumentException();
        }
        skins = select.attr("data-imgname");
    }

    private void convertToSkillList(Elements select) throws IllegalArgumentException {
        if (select == null) {
            Timber.e("Convert to skills fail, null pointer items");
            throw new IllegalArgumentException();
        }
        skills = new ArrayList<>();
        for (Element item : select) {
            try {
                String name = item.selectFirst("p.skill-name > b").text();
                if (name.isEmpty()) {
                    continue;
                }
                Elements spans = item.select("p.skill-name > span");
                String cd = "", consume = "";
                if (spans.size() <= 2) {
                    cd = spans.get(0).text();
                    consume = spans.get(1).text();
                }
                String description = item.selectFirst("p.skill-desc").text();
                String tips = item.selectFirst("div.skill-tips").text();
                skills.add(new Skill(name, cd, consume, description, tips));
            } catch (NullPointerException e) {
                Timber.e("Convert to skill fail, with element %s", item.html());
                throw new IllegalArgumentException(item.html());
            }
        }
    }

    private void convertToSuggestSkills(Elements select) throws IllegalArgumentException {
        if (select == null || select.size() != 2) {
            Timber.e("Convert to suggest skills fail, null pointer items");
            throw new IllegalArgumentException();
        }
        for (int i = 0; i < 2; i++) {
            Element item = select.get(i);
            try {
                String src = item.attr("src");
                int value = Integer.parseInt(src.substring(src.length() - 6, src.length() - 5));
                if (i == 0) {
                    suggestFirstSkill = value;
                } else {
                    suggestSecondSkill = value;
                }
            } catch (NullPointerException e) {
                Timber.e("Convert to skill fail, with element %s", item.html());
                throw new IllegalArgumentException(item.html());
            }
        }
    }

    private void convertToSuggestSummoners(Elements select) throws IllegalArgumentException {
        if (select == null) {
            Timber.e("Convert to suggest summoners fail, null pointer items");
            throw new IllegalArgumentException();
        }
        suggestSummoners = select.attr("data-skill");
    }

    private void convertToHeroRelations(Elements select) throws IllegalArgumentException {
        if (select == null || select.size() != 3) {
            Timber.e("Convert to hero relations fail, null pointer items");
            throw new IllegalArgumentException();
        }
        relations = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            Element item = select.get(i);
            try {
                Elements ids = item.select("ul > li > a");
                Elements descriptions = item.select("div > p");
                if (ids.size() != descriptions.size()) {
                    Timber.e("size not the same");
                    throw new NullPointerException();
                }
                for (int j = 0; j < ids.size(); j++) {
                    String id = ids.get(j).attr("href");
                    int value = Integer.parseInt(id.substring(0, id.indexOf('.')));
                    String description = descriptions.get(j).text();
                    relations.add(new Relation(value, i, description));
                }
            } catch (NullPointerException e) {
                Timber.e("Convert to hero relations fail, with element %s", item.html());
                throw new IllegalArgumentException(item.html());
            }
        }
    }

    private void convertToSuggestItems(Elements select) throws IllegalArgumentException {
        if (select == null || select.size() != 2) {
            Timber.e("Convert to suggest items fail, null pointer items");
            throw new IllegalArgumentException();
        }
        for (int i = 0; i < 2; i++) {
            Element item = select.get(i);
            try {
                if (i == 0) {
                    suggestFirstItems = item.selectFirst("ul").attr("data-item");
                    suggestFirstItemsDescription = item.selectFirst("p").text();
                } else {
                    suggestSecondItems = item.selectFirst("ul").attr("data-item");
                    suggestSecondItemsDescription = item.selectFirst("p").text();
                }
            } catch (NullPointerException e) {
                Timber.e("Convert to suggest items fail, with element %s", item.html());
                throw new IllegalArgumentException(item.html());
            }
        }
    }

    private void convertToSuggestInscriptions(Elements select) throws IllegalArgumentException {
        if (select == null) {
            Timber.e("Convert to suggest inscriptions fail, null pointer items");
            throw new IllegalArgumentException();
        }
        try {
            suggestInscriptions = select.select("ul").attr("data-ming");
            suggestInscriptionsDescription = select.select("p").text();
        } catch (NullPointerException e) {
            Timber.e("Convert to suggest inscriptions fail, with element %s", select.html());
            throw new IllegalArgumentException(select.html());
        }
    }

    private void convertToStory(Elements select) throws IllegalArgumentException {
        if (select == null) {
            Timber.e("Convert to story fail, null pointer items");
            throw new IllegalArgumentException();
        }
        story = select.html();
        story = story.replace("<br>", "\n\n");
        story = story.replace("\n\n\n\n", "\n\n");
    }
}
