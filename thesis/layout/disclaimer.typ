#import "/layout/fonts.typ": *

#let disclaimer(
  title: "",
  degree: "",
  author: "",
  submissionDate: datetime,
) = {
  set page(
    margin: (left: 30mm, right: 30mm, top: 40mm, bottom: 40mm),
    numbering: none,
    number-align: center,
  )

  set text(
    font: fonts.body,
    size: 12pt,
    lang: "en",
  )

  set par(leading: 1em)

  // --- Disclaimer ---
  v(65%)
  text(
    "I confirm that this "
      + degree
      + "’s thesis is my own work and I have documented all sources and material used and have relied exclusively on the cited sources and materials; in particular, direct or indirect quotations are identified as such. I am aware that a violation of these provisions may result in the revocation of my academic degree, even retroactively. Furthermore, I certify that the electronic version matches the printed copies.",
  )

  v(15mm)
  grid(
    columns: 2,
    gutter: 1fr,
    "Leipzig, " + submissionDate.display("[day].[month].[year]"), author,
  )
}
