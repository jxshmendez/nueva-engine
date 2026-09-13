#pragma once

namespace eng {

class Application {
public:
  virtual bool Init() = 0;
  virtual void Update(float deltaTime) = 0; // seconds
  virtual void Destroy() = 0;

  void SetNeedsToBeClosed(bool value);
  bool NeedsToBeClosed() const;

private:
  bool m_needsToBeClosed = false;
};

} // namespace eng
