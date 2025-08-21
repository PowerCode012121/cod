#pragma once

void Text(Vector2 pos, ImColor col, std::string text)
{
	if (cfg::drop_shadow)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + 1, pos.y), ImColor(30, 30, 30), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + 1, pos.y + 1), ImColor(30, 30, 30), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y + 1), ImColor(30, 30, 30), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y), col, text.c_str());
}

void Box(Vector2 pos, Vector2 size, ImColor col)
{
	// top
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y), col);
	//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x - 2, pos.y - 1), ImVec2(pos.x + size.x + 2, pos.y - 1), ImColor(30, 30, 30));
	//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + 1, pos.y + 1), ImVec2(pos.x + size.x - 1, pos.y + 1), ImColor(30, 30, 30));

	// bottom
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y + size.y), ImVec2(pos.x + size.x, pos.y + size.y), col);
	//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + 1, pos.y + size.y - 1), ImVec2(pos.x + size.x - 1, pos.y + size.y - 1), ImColor(30, 30, 30));
	//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x - 2, pos.y + size.y + 1), ImVec2(pos.x + size.x + 2, pos.y + size.y + 1), ImColor(30, 30, 30));

	// left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y + size.y), col);
	//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x - 1, pos.y), ImVec2(pos.x - 1, pos.y + size.y), ImColor(30, 30, 30));
	//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + 1, pos.y + 1), ImVec2(pos.x + 1, pos.y + size.y - 1), ImColor(30, 30, 30));

	// right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + size.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.y), col);
	//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + size.x - 1, pos.y + 1), ImVec2(pos.x + size.x - 1, pos.y + size.y - 1), ImColor(30, 30, 30));
	//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + size.x + 1, pos.y), ImVec2(pos.x + size.x + 1, pos.y + size.y), ImColor(30, 30, 30));
}

void FilledBox(Vector2 pos, Vector2 size, ImColor col)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.y), col);
}

void DrawHeadCircle(Vector3 head, ImColor col)
{
	Vector2 head_screen;
	if (!world_to_screen(head, head_screen, globals::cam_pos, globals::ref_def)) return;

	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_screen.x, head_screen.y), 2.f, col);
}