# TIP.md

## 📌 커밋 메시지 규칙

### 1. 기본 구조

```
타입: 내용
```

### 예시

```
feat: add ultimate skill system
fix: resolve defense not resetting bug
chore: add .gitignore for build artifacts
```

---

## 🧩 타입 종류 (필수 암기)

### ✨ feat

* 새로운 기능 추가

```
feat: add critical hit system
```

---

### 🐛 fix

* 버그 수정

```
fix: defense state not resetting after turn
```

---

### 🔧 chore

* 기타 작업 (설정, 파일 추가 등)

```
chore: add .gitignore
```

---

### ♻️ refactor

* 기능 변화 없이 코드 구조 개선

```
refactor: simplify damage calculation logic
```

---

### 📝 docs

* 문서 관련 변경 (README, LOG 등)

```
docs: update LOG.md
```

---

### 🎨 style

* 코드 스타일 수정 (기능 변화 없음)

```
style: format code indentation
```

---

## 💡 작성 규칙

### ✔ 영어로 작성 (추천)

* 협업/가독성 때문

---

### ✔ 한 줄로 간결하게

```
feat: add gauge system
```

---

### ✔ 동사 원형 사용

```
add ❌ added ❌ adding ❌
```

---

### ✔ 불필요한 설명 금지

```
❌ feat: I added a new system for...
✔ feat: add gauge system
```

---

## 🚫 하지 말 것

```
❌ "수정함"
❌ "코딩함"
❌ "버그 고침"
```

👉 의미가 모호함

---

## 🚀 추천 루틴

코딩 후 항상:

```
git add .
git commit -m "타입: 내용"
git push
```

---

## 🎯 예시 모음

```
feat: add ultimate skill system
feat: implement enemy AI logic
fix: correct damage calculation bug
chore: initialize project
docs: add LOG.md
```

---

## 🔥 한 줄 요약

타입 + 무엇을 했는지
